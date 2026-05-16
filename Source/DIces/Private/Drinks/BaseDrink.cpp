

#include "Drinks/BaseDrink.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BasePlayer.h"
#include "Player/Conditions/BaseCondition.h"
#include "Algo/RandomShuffle.h"

// Sets default values
ABaseDrink::ABaseDrink()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BottleBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle"));
	RootComponent = BottleBase;
}

// Called when the game starts or when spawned
void ABaseDrink::BeginPlay()
{
	Super::BeginPlay();
	bIsPlayer = false;

	BottleBase->SetSimulatePhysics(false);
	OnClicked.AddDynamic(this, &ABaseDrink::AddToPlayer);

	Player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
}

// Called every frame
void ABaseDrink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseDrink::AddToPlayer(AActor* ActorClicked, FKey InKey)
{
	if (!bCanBeClicked) return;
	if (!bIsPlayer && Player->GetGoldQuantity() >= GoldPrice)
	{
		Player->RemoveGold(GoldPrice);
		TArray DrinkSpot{ 0, 1, 2, 3, 4, 5 };
		Algo::RandomShuffle(DrinkSpot);
		for (int i = 0; i < 6; i++)
		{
			if (Player->bIsDrinkSpotTaken[DrinkSpot[i]]) continue;
				
			bIsPlayer = true;
			Player->bIsDrinkSpotTaken[DrinkSpot[i]] = true;
			SetActorLocation(Player->DrinksOnTable[DrinkSpot[i]], false, nullptr, ETeleportType::None);
			DrinkTaken.ExecuteIfBound();
			break;
		}
	}
	else if (bIsPlayer)
	{
		Drink();
	}
}

void ABaseDrink::Drink()
{
	for (UBaseCondition* Condition : Player->DrinkConditions)
	{
		if (Condition == nullptr)
		{
			Condition = NewObject<UBaseCondition>(Player);
			Condition->RegisterComponent();
			break;
		}		
	}
	Destroy();
}

