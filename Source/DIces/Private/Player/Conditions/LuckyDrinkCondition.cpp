

#include "Player/Conditions/LuckyDrinkCondition.h"
#include "Player/BasePlayer.h"

void ULuckyDrinkCondition::BeginPlay()
{
	Super::BeginPlay();
	ComponentTags.Add(FName("Lucky"));
	bHasRerolled = false;
}

void ULuckyDrinkCondition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	bCanReroll = !IsValid(Player->PlayerDicesOnTable[0]);
	
	if (ActualTurnCount - StartTurnCount >= TurnLifetime)
	{
		DestroyComponent();
		return;
	}
	if (ActualTurnCount - NewTurnCount == 1)
	{
		++NewTurnCount;
		bHasRerolled = false;
	}
}

void ULuckyDrinkCondition::DrinkEffect()
{
	//Dice Reroll
	if (bCanReroll && !bHasRerolled)
	{
		if (Player->Get_bPlayerDiceRolled())
		{
			for (ABaseDice* Dice : Player->PlayerDicesOnHand)
			{
				if (!IsValid(Dice)) continue;
				Dice->PlayerRolling();
				Dice->bIsRolled = true;
			}
		}
		bHasRerolled = true;
	}
}