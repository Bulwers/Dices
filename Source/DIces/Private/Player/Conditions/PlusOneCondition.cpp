// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Conditions/PlusOneCondition.h"


void UPlusOneCondition::BeginPlay()
{
	Super::BeginPlay();
	ComponentTags.Add(FName("PlusOne"));
	ComponentTags.Add(FName("DiceBuff"));
	bCanBuff = true;
}

void UPlusOneCondition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActualTurnCount - StartTurnCount >= 3)
	{

		DestroyComponent();
	}
	// Turn Reset
	if (ActualTurnCount - NewTurnCount >= 1)
	{
		++NewTurnCount;
		bCanBuff = true;
	}
}

void UPlusOneCondition::DrinkEffect()
{
	bCanBuff = false;
	Player->bPlusOneBuff = false;
	Player->bPlusTwoBuff = false;
}
