

#include "Waiter/Waiter.h"
#include "Components/CapsuleComponent.h"
#include "Game/GameStateBaseClass.h"
#include "Algo/RandomShuffle.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BasePlayer.h"
#include "Game/GameManagers/BrawlManager.h"
#include "Game/GameManagers/WaiterManager.h"

AWaiter::AWaiter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComponent;

	PlatePosition = CreateDefaultSubobject<USceneComponent>(TEXT("Plate"));
	PlatePosition->SetupAttachment(CapsuleComponent);

	DrinkSpot_1 = CreateDefaultSubobject<USceneComponent>(TEXT("Spot_1"));
	DrinkSpot_1->SetupAttachment(PlatePosition);

	DrinkSpot_2 = CreateDefaultSubobject<USceneComponent>(TEXT("Spot_2"));
	DrinkSpot_2->SetupAttachment(PlatePosition);

	DrinkSpot_3 = CreateDefaultSubobject<USceneComponent>(TEXT("Spot_3"));
	DrinkSpot_3->SetupAttachment(PlatePosition);
	bCanDismiss = false;
}

void AWaiter::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<AGameStateBaseClass>(UGameplayStatics::GetGameState(GetWorld()));
	SetActorLocationAndRotation(StartLoc, StartRot, false, nullptr, ETeleportType::None);
	GameState->GetWaiterManager()->WaiterCall.BindUObject(this, &AWaiter::DrinkOffer);

	DrinkTier = GameState->GetEnemiesCount();
}

void AWaiter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaiter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWaiter::SetStartingLocAndRot()
{
	SetActorLocationAndRotation(StartLoc, StartRot, false, nullptr, ETeleportType::None);
	if (Drink_1)
	{
		Drink_1->DrinkTaken.Unbind();
		if (!Drink_1->bIsPlayer)
		{
			Drink_1->Destroy();
		}
		Drink_1 = nullptr;
	}
	if (Drink_2)
	{
		Drink_2->DrinkTaken.Unbind();
		if (!Drink_2->bIsPlayer)
		{
			Drink_2->Destroy();
		}
		Drink_2 = nullptr;
	}
	if (Drink_3)
	{
		Drink_3->DrinkTaken.Unbind();
		if (!Drink_3->bIsPlayer)
		{
			Drink_3->Destroy();
		}
		Drink_3 = nullptr;
	}
	GameState->GetPlayer()->MoveCamera(ECamPosition::Bottom);
	GameState->GetBrawlManager()->SetWaiterState();
	bCanDismiss = false;
}

void AWaiter::DrinkOffer()
{ 
	UE_LOG(LogTemp, Warning, TEXT("Waiter Offering Drinks"));
	SetActorLocationAndRotation(ServeLoc, ServeRot, false, nullptr, ETeleportType::None);
	GameState->GetPlayer()->MoveCamera(ECamPosition::Waiter);
	bCanDismiss = true;

	DrinkTier = GameState->GetEnemiesCount();

	FVector2D RandDrinksLvl_1 = RandDrinks(DrinksLvl_1);
	FVector2D RandDrinksLvl_2 = RandDrinks(DrinksLvl_2);
	FVector2D RandDrinksLvl_3 = RandDrinks(DrinksLvl_3);

	int PercentChance = FMath::RandRange(0, 100);

	if (DrinkTier >= 8)
	{
		if (PercentChance > ChanceOfLvl_123)
		{
			DrinkSpawn(RandDrinksLvl_1.X, RandDrinksLvl_2.X, RandDrinksLvl_3.X);
		}
		else if (PercentChance > ChanceOfLvl_122)
		{
			DrinkSpawn(RandDrinksLvl_1.X, RandDrinksLvl_2.X, RandDrinksLvl_2.Y);
		}
		else if (PercentChance > ChanceOfLvl_113)
		{
			DrinkSpawn(RandDrinksLvl_1.X, RandDrinksLvl_1.Y, RandDrinksLvl_3.X);
		}
		else
		{
			DrinkSpawn(RandDrinksLvl_1.X, RandDrinksLvl_1.Y, RandDrinksLvl_2.X);
		}
	}
	else if (DrinkTier == 5)
	{
		if (PercentChance > ChanceOfLvl_12)
		{
			DrinkSpawn(RandDrinksLvl_1.X, RandDrinksLvl_2.X, -1);
		}
		else
		{
			DrinkSpawn(RandDrinksLvl_1.X, RandDrinksLvl_1.Y, -1);
		}
	}
	else
	{
		DrinkSpawn(RandDrinksLvl_1.X, -1, -1);
	}
	
}

void AWaiter::DrinkSpawn(int DrinkToSpawn_1, int DrinkToSpawn_2, int DrinkToSpawn_3)
{
	if (DrinkToSpawn_2 == -1 && DrinkToSpawn_3 == -1)
	{
		Drink_1 = GetWorld()->SpawnActor<ABaseDrink>(DrinkToSpawn[DrinkToSpawn_1],
			DrinkSpot_2->GetComponentLocation(), DrinkSpot_2->GetComponentRotation());
		Drink_1->SetCanBeClicked();
		Drink_1->DrinkTaken.BindUObject(this, &AWaiter::SetStartingLocAndRot);
	}
	else if (DrinkToSpawn_3 == -1)
	{
		Drink_1 = GetWorld()->SpawnActor<ABaseDrink>(DrinkToSpawn[DrinkToSpawn_1],
			DrinkSpot_1->GetComponentLocation(), DrinkSpot_1->GetComponentRotation());
		Drink_1->SetCanBeClicked();
		Drink_1->DrinkTaken.BindUObject(this, &AWaiter::SetStartingLocAndRot);

		Drink_2 = GetWorld()->SpawnActor<ABaseDrink>(DrinkToSpawn[DrinkToSpawn_2],
			DrinkSpot_3->GetComponentLocation(), DrinkSpot_3->GetComponentRotation());
		Drink_2->SetCanBeClicked();
		Drink_2->DrinkTaken.BindUObject(this, &AWaiter::SetStartingLocAndRot);
	}
	else
	{
		Drink_1 = GetWorld()->SpawnActor<ABaseDrink>(DrinkToSpawn[DrinkToSpawn_1],
			DrinkSpot_1->GetComponentLocation(), DrinkSpot_1->GetComponentRotation());
		Drink_1->SetCanBeClicked();
		Drink_1->DrinkTaken.BindUObject(this, &AWaiter::SetStartingLocAndRot);

		Drink_2 = GetWorld()->SpawnActor<ABaseDrink>(DrinkToSpawn[DrinkToSpawn_2],
			DrinkSpot_2->GetComponentLocation(), DrinkSpot_2->GetComponentRotation());
		Drink_2->SetCanBeClicked();
		Drink_2->DrinkTaken.BindUObject(this, &AWaiter::SetStartingLocAndRot);

		Drink_3 = GetWorld()->SpawnActor<ABaseDrink>(DrinkToSpawn[DrinkToSpawn_3],
			DrinkSpot_3->GetComponentLocation(), DrinkSpot_3->GetComponentRotation());
		Drink_3->SetCanBeClicked();
		Drink_3->DrinkTaken.BindUObject(this, &AWaiter::SetStartingLocAndRot);
	}
}

FVector2D AWaiter::RandDrinks(TArray<int> DrinksLvl)
{
	Algo::RandomShuffle(DrinksLvl);

	int FirstDrink = DrinksLvl[0];
	int SecondDrink = DrinksLvl[1];

	return FVector2D (FirstDrink, SecondDrink);
}
