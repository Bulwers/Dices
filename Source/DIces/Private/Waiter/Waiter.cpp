

#include "Waiter/Waiter.h"
#include "Components/CapsuleComponent.h"
#include "Game/GameStateBaseClass.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BasePlayer.h"
#include "Drinks/BaseDrink.h"
#include "Game/GameManagers/BrawlManager.h"
#include "Game/GameManagers/WaiterManager.h"

AWaiter::AWaiter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComponent;

	PlatePosition = CreateDefaultSubobject<USceneComponent>(TEXT("Plate"));
	PlatePosition->SetupAttachment(CapsuleComponent);

	for (int32 i = 0; i < 3; i++)
	{
		DrinkSpots.Add(CreateDefaultSubobject<USceneComponent>(FName(*FString::Printf(TEXT("Spot_%d"), i + 1))));
		DrinkSpots[i]->SetupAttachment(PlatePosition);
	}
	bCanDismiss = false;
	
}

void AWaiter::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<AGameStateBaseClass>(UGameplayStatics::GetGameState(GetWorld()));
	if (!IsValid(GameState))
	{
		UE_LOG(LogTemp, Error, TEXT("GameState not found / AWaiter::BeginPlay()"));
	}
	
	GameState->GetWaiterManager()->WaiterCall.BindUObject(this, &AWaiter::DrinkOffer);
	SetActorLocationAndRotation(StartLoc, StartRot, false, nullptr, ETeleportType::None);
	DrinkTier = GameState->GetEnemiesCount();
}

void AWaiter::SetStartingLocAndRot()
{
	SetActorLocationAndRotation(StartLoc, StartRot, false, nullptr, ETeleportType::None);
	
	for (TObjectPtr<ABaseDrink>& Drink : ActiveDrinks)
	{
		if (!Drink) continue;
		
		Drink->DrinkTaken.Unbind();	
		if (!Drink->bIsPlayer) Drink->Destroy();
		Drink = nullptr;
	}
	ActiveDrinks.Empty();
	
	if (GameState)
	{
		GameState->GetPlayer()->MoveCamera(ECamPosition::Bottom);
		GameState->GetBrawlManager()->SetWaiterState();
	}
	bCanDismiss = false;
}

void AWaiter::DrinkOffer()
{ 
	if (!IsValid(GameState))
	{
		UE_LOG(LogTemp, Error, TEXT("GameState not found / AWaiter::DrinkOffer()"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Waiter Offering Drinks"));
	SetActorLocationAndRotation(ServeLoc, ServeRot, false, nullptr, ETeleportType::None);
	GameState->GetPlayer()->MoveCamera(ECamPosition::Waiter);
	bCanDismiss = true;

	DrinkTier = GameState->GetEnemiesCount();

	TArray<int32> RandDrinksLvl_1 = RandDrinks(DrinksLvl_1);
	TArray<int32> RandDrinksLvl_2 = RandDrinks(DrinksLvl_2);
	TArray<int32> RandDrinksLvl_3 = RandDrinks(DrinksLvl_3);
	
	int32 PercentChance = FMath::RandRange(0, 100);

	if (DrinkTier >= 8)
	{
		if (PercentChance > ChanceOfLvl_123)
		{
			SpawnSelectedDrinks({RandDrinksLvl_1[0], RandDrinksLvl_2[0], RandDrinksLvl_3[0]});
		}
		else if (PercentChance > ChanceOfLvl_122)
		{
			SpawnSelectedDrinks({RandDrinksLvl_1[0], RandDrinksLvl_2[0], RandDrinksLvl_2[1]});
		}
		else if (PercentChance > ChanceOfLvl_113)
		{
			SpawnSelectedDrinks({RandDrinksLvl_1[0], RandDrinksLvl_1[1], RandDrinksLvl_3[0]});
		}
		else
		{
			SpawnSelectedDrinks({RandDrinksLvl_1[0], RandDrinksLvl_1[0], RandDrinksLvl_2[0]});
		}
	}
	else if (DrinkTier == 5)
	{
		if (PercentChance > ChanceOfLvl_12)
		{
			SpawnSelectedDrinks({RandDrinksLvl_1[0], RandDrinksLvl_2[0]});
		}
		else
		{
			SpawnSelectedDrinks({RandDrinksLvl_1[0], RandDrinksLvl_1[1]});
		}
	}
	else
	{
		SpawnSelectedDrinks({RandDrinksLvl_1[0]});
	}
	
}

void AWaiter::SpawnSelectedDrinks(const TArray<int32>& DrinksIndexes)
{
	ActiveDrinks.Empty();

	if (!GetWorld())
	{
		return;
	}

	TArray<int32> SpotIndexes;

	if (DrinksIndexes.Num() == 1)
	{
		SpotIndexes = { 1 };
	}
	else if (DrinksIndexes.Num() == 2)
	{
		SpotIndexes = { 0, 2 };
	}
	else if (DrinksIndexes.Num() == 3)
	{
		SpotIndexes = { 0, 1, 2 };
	}
	else
	{
		return;
	}

	for (int32 i = 0; i < DrinksIndexes.Num(); i++)
	{
		const int32 DrinkIndex = DrinksIndexes[i];
		const int32 SpotIndex = SpotIndexes[i];

		if (!DrinkToSpawn.IsValidIndex(DrinkIndex) || !DrinkSpots.IsValidIndex(SpotIndex))
		{
			continue;
		}

		ABaseDrink* SpawnedDrink = GetWorld()->SpawnActor<ABaseDrink>(
			DrinkToSpawn[DrinkIndex],
			DrinkSpots[SpotIndex]->GetComponentLocation(),
			DrinkSpots[SpotIndex]->GetComponentRotation()
		);

		if (!SpawnedDrink)
		{
			continue;
		}

		SpawnedDrink->SetCanBeClicked();
		SpawnedDrink->DrinkTaken.BindUObject(this, &AWaiter::SetStartingLocAndRot);
		ActiveDrinks.Add(SpawnedDrink);
	}
}

TArray<int32> AWaiter::RandDrinks(const TArray<int32>& DrinksLvl)
{
	TArray<int32> RandomDrinks;
	if (DrinksLvl.IsEmpty()) return RandomDrinks;
	
	int32 FirstIndex = FMath::RandRange(0, DrinksLvl.Num() - 1);
	RandomDrinks.Add(DrinksLvl[FirstIndex]);
	
	if (DrinksLvl.Num() == 1)
	{
		return RandomDrinks;
	}
	
	int32 SecondIndex;
	do
	{
		SecondIndex = FMath::RandRange(0, DrinksLvl.Num() - 1);
	}
	while (SecondIndex == FirstIndex);
	
	RandomDrinks.Add(DrinksLvl[SecondIndex]);

	return  RandomDrinks;
}
