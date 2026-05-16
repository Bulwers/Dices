// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameManagers/TurnManager.h"

// Sets default values for this component's properties
UTurnManager::UTurnManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UTurnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UTurnManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// Setting first player for brawl
void UTurnManager::WhoseFirst(bool bIsPlayerFirst)
{
	if (bIsPlayerFirst == true)
	{
		ECurrentTurn = ECurrentTurn::PlayerTurn;
	}
	else
	{
		ECurrentTurn = ECurrentTurn::EnemyTurn;
	}
}

// Swapping order for player and enemy turns
void UTurnManager::SwapOrder()
{
	if (ECurrentTurn == ECurrentTurn::PlayerTurn)
	{
		ECurrentTurn = ECurrentTurn::EnemyTurn;
	}
	else if (ECurrentTurn == ECurrentTurn::EnemyTurn)
	{
		ECurrentTurn = ECurrentTurn::PlayerTurn;
	}
}

// Checking if it's player's turn
bool UTurnManager::IsPlayerTurn() const
{
	return ECurrentTurn == ECurrentTurn::PlayerTurn;
}

// Setting waiting turn for brawl
void UTurnManager::SetWaitingTurn()
{
	ECurrentTurn = ECurrentTurn::Waiting;
}
