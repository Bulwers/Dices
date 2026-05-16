// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Conditions/LuckyDrinkCondition.h"

void ULuckyDrinkCondition::BeginPlay()
{
	Super::BeginPlay();
	ComponentTags.Add(FName("Lucky"));
	bHasRerolld = false;
}

void ULuckyDrinkCondition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Player->PlayerDicesOnTable[0])
	{
		bCanRereoll = false;
	}
	if (Player->PlayerDicesOnTable[0] == nullptr)
	{
		bCanRereoll = true;
	}

	// Reseting bHasRerolld
	if (ActualTurnCount - NewTurnCount == 1)
	{
		NewTurnCount++;
		bHasRerolld = false;
	}

	// Lifetime
	if (ActualTurnCount - StartTurnCount >= 3)
	{

		DestroyComponent();
	}
}

void ULuckyDrinkCondition::DrinkEffect()
{
	//Dice Reroll
	if (bCanRereoll && !bHasRerolld)
	{
		if (Player->Get_bPlayerDiceRolled())
		{
			for (int i : { 0, 1, 2, 3, 4, 5 })
			{
				Player->PlayerDicesOnHand[i]->PlayerRolling();
				Player->PlayerDicesOnHand[i]->bIsRolled = true;
			}
		}
		bHasRerolld = true;
	}
}