// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Comp/JumpingDiceComponent.h"
#include "Enemies/BaseEnemy.h"

UJumpingDiceComponent::UJumpingDiceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UJumpingDiceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UJumpingDiceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJumpingDiceComponent::FakeDiceCheck(ABaseEnemy* Owner)
{
	for (int i = 0; i <= 5; i++)
	{
		if (Owner->EnemyDicesOnTable[i] && Owner->PlayerDicesOnTable[i] &&
			Owner->EnemyDicesOnTable[i]->ActorHasTag(FName("Fake Dice")) &&
			Owner->PlayerDicesOnTable[i]->Result() - Owner->EnemyDicesOnTable[i]->Result() >= 2)
		{
			for (ABaseDice* Dice : Owner->EnemyDicesOnTable)
			{
				if (Dice && Dice->bIsStopped)
				{
					Dice->DiceJump();
				}
			}
			// add delegate
			Owner->TableHit();
			break;
		}
	}
}