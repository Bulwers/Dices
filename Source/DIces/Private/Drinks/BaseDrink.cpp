

#include "Drinks/BaseDrink.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BasePlayer.h"
#include "Player/Conditions/BaseCondition.h"
#include "Algo/RandomShuffle.h"

ABaseDrink::ABaseDrink()
{
	PrimaryActorTick.bCanEverTick = false;

	BottleBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle"));
	RootComponent = BottleBase;
}

void ABaseDrink::BeginPlay()
{
	Super::BeginPlay();
	bIsPlayer = false;

	BottleBase->SetSimulatePhysics(false);
	OnClicked.AddDynamic(this, &ABaseDrink::AddToPlayer);

	Player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!IsValid(Player))
	{
		UE_LOG(LogTemp, Error, TEXT("Player not found / ABaseDrink"));
	}
}

void ABaseDrink::AddToPlayer(AActor* ActorClicked, FKey InKey)
{
	if (!bCanBeClicked || !IsValid(Player)) return;
	if (!bIsPlayer)
	{
		if (Player->GetGoldQuantity() < GoldPrice) return;
		
		TArray DrinkSpot{ 0, 1, 2, 3, 4, 5 };
		Algo::RandomShuffle(DrinkSpot);
		for (const int32 SpotIndex : DrinkSpot)
		{
			if (!Player->bIsDrinkSpotTaken.IsValidIndex(SpotIndex) || !Player->DrinksOnTable.IsValidIndex(SpotIndex)) continue;
			if (Player->bIsDrinkSpotTaken[SpotIndex]) continue;
				
			Player->RemoveGold(GoldPrice);
			
			bIsPlayer = true;
			PlayerDrinkSlot = SpotIndex;
			Player->bIsDrinkSpotTaken[SpotIndex] = true;
			SetActorLocation(Player->DrinksOnTable[SpotIndex], false, nullptr, ETeleportType::None);
			DrinkTaken.ExecuteIfBound();
			break;
		}
		UE_LOG(LogTemp, Warning, TEXT("No free drink spot / ABaseDrink"));
	}
	else
	{
		Drink();
	}
}

void ABaseDrink::Drink()
{
	if (!IsValid(Player)) return;
	if (!ConditionToApply)
	{
		UE_LOG(LogTemp, Error, TEXT("ConditionToApply is not set / ABaseDrink"));
		return;
	}
	
	for (TObjectPtr<UBaseCondition>& Condition : Player->DrinkConditions)
	{
		if (!IsValid(Condition))
		{
			Condition = NewObject<UBaseCondition>(Player, ConditionToApply);
			if (!IsValid(Condition))
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to create drink condition / ABaseDrink"));
				return;
			}
			Condition->RegisterComponent();
			Condition->TurnLifetime = ConditionLifetime;
			break;
		}
	}
	if (Player->bIsDrinkSpotTaken.IsValidIndex(PlayerDrinkSlot))
	{
		Player->bIsDrinkSpotTaken[PlayerDrinkSlot] = false;
	}
	PlayerDrinkSlot = INDEX_NONE;
	Destroy();
}

