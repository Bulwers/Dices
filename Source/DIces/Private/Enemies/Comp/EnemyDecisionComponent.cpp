// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Comp/EnemyDecisionComponent.h"
#include "Dices/BaseDice.h"
#include "Enemies/EnemyStrategy.h"

UEnemyDecisionComponent::UEnemyDecisionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UEnemyDecisionComponent::BeginPlay()
{
	Super::BeginPlay();

	Strategy = NewObject<UEnemyStrategy>();
	Strategy->InitNameAndData(StrategyName);
}

void UEnemyDecisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

int UEnemyDecisionComponent::FindSlotToPlaceDice(
	const TArray<ABaseDice*>& PlayerDicesOnTable,
	const TArray<ABaseDice*>& EnemyDicesOnTable)
{
	for (const int i : { 0, 1, 2, 3, 4, 5 })
	{
		if (PlayerDicesOnTable[i] == nullptr && EnemyDicesOnTable[i] == nullptr)
		{
			EEnemyPlacementDecision = EDicePlacementDecision::BlindPlacement;
			return i;
    	}
		if (PlayerDicesOnTable[i] != nullptr && EnemyDicesOnTable[i] == nullptr)
		{
			EEnemyPlacementDecision = EDicePlacementDecision::KnowingPlacement;
			return i;
		}
	}
	return -1;
}

ABaseDice* UEnemyDecisionComponent::ChoosingDiceToPutOnTable(
	const TArray<ABaseDice*>& PlayerDicesOnTable,
	const TArray<ABaseDice*>& EnemyDicesOnTable,
	const TArray<ABaseDice*>& EnemyDices)
{
	int Slot = FindSlotToPlaceDice(PlayerDicesOnTable, EnemyDicesOnTable);
	int BestResultScore = -1;
	int BestResultIndex = -1;
	
	TArray<int> EnemyAvailableDices;
	for (const int i : { 0, 1, 2, 3, 4, 5})
	{
		if (!EnemyDices[i]->bIsEnemyChoosen)
		{
			EnemyAvailableDices.Add(i);
		}
	}
	
	switch (EEnemyPlacementDecision)
	{
	case EDicePlacementDecision::KnowingPlacement:
		for (const int Index : EnemyAvailableDices)
		{
			int Score = Strategy->ResultsScore(PlayerDicesOnTable[Slot]->Result(), EnemyDices[Index]->Result());
			if (Score > BestResultScore)
			{
				BestResultScore = Score;
				BestResultIndex = Index;
			}
		}
		break;
	case EDicePlacementDecision::BlindPlacement:
		for (const int Index : EnemyAvailableDices)
		{
			int Score = Strategy->BlindScore(EnemyDices[Index]->Result());
			if (Score > BestResultScore)
			{
				BestResultScore = Score;
				BestResultIndex = Index;
			}
		}
		break;
	}

	if (BestResultIndex != -1)
	{
		return EnemyDices[BestResultIndex];
	}
	return EnemyDices[EnemyAvailableDices[0]];
}