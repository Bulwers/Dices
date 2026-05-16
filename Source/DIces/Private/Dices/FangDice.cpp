// Fill out your copyright notice in the Description page of Project Settings.


#include "Dices/FangDice.h"

AFangDice::AFangDice()
{
	// Setting tag
	Tags.Add(FName("Fang"));
}

void AFangDice::BeginPlay()
{
	Super::BeginPlay();
	
	bIsRolled = true;
	
	bIsPlayer = true;
	bIsChoosen = true;
	bIsEnemyChoosen = false;
	bCanHighlight = false;
	bIsStopped = true;
	bIsVisible = true;
}

int AFangDice::Result()
{
	return 6;
}
