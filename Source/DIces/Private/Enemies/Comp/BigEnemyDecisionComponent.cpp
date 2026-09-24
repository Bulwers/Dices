

#include "Enemies/Comp/BigEnemyDecisionComponent.h"
#include "Dices/BaseDice.h"
#include "Enemies/EnemyStrategy.h"


int32 UBigEnemyDecisionComponent::FindSlotToPlaceDice(
	const TArray<ABaseDice*>& PlayerDicesOnTable, 
	const TArray<ABaseDice*>& EnemyDicesOnTable)
{
	for (const int32 i : { 0, 2, 4 })
	{
		if (PlayerDicesOnTable[i] == nullptr &&
			PlayerDicesOnTable[i + 1] == nullptr &&
			EnemyDicesOnTable[i] == nullptr &&
			EnemyDicesOnTable[i + 1] == nullptr)
		{
			EEnemyPlacementDecision =
				EDicePlacementDecision::BlindPlacement;

			return i;
		}

		if ((PlayerDicesOnTable[i] != nullptr ||
			 PlayerDicesOnTable[i + 1] != nullptr) &&
			EnemyDicesOnTable[i] == nullptr &&
			EnemyDicesOnTable[i + 1] == nullptr)
		{
			EEnemyPlacementDecision =
				EDicePlacementDecision::KnowingPlacement;

			return i;
		}
	}

	return INDEX_NONE;
}

ABaseDice* UBigEnemyDecisionComponent::ChoosingDiceToPutOnTable(
	const TArray<ABaseDice*>& PlayerDicesOnTable, 
	const TArray<ABaseDice*>& EnemyDices, 
	const int32 Slot)
{
	if (!IsValid(Strategy))
	{
		return nullptr;
	}
	
	TArray<int32> EnemyAvailableDices;
	for (int32 i = 0; i < EnemyDices.Num(); i++)
	{
		if (IsValid(EnemyDices[i]) && !EnemyDices[i]->bIsEnemyChosen)
		{
			EnemyAvailableDices.Add(i);
		}
	}
	if (EnemyAvailableDices.IsEmpty())
	{
		return nullptr;
	}
	
	const int32 PlayerFirst = PlayerDicesOnTable[Slot] ? PlayerDicesOnTable[Slot]->Result() : 0;
	const int32 PlayerSecond = (Slot + 1 < PlayerDicesOnTable.Num() && PlayerDicesOnTable[Slot + 1]) ? PlayerDicesOnTable[Slot + 1]->Result() : 0;
	const int32 MaxResult = FMath::Max(PlayerFirst, PlayerSecond);
	
	int32 BestResultScore = -1;
	int32 BestResultIndex = INDEX_NONE;
	
	switch (EEnemyPlacementDecision)
	{
	case EDicePlacementDecision::KnowingPlacement:
		if (!PlayerDicesOnTable.IsValidIndex(Slot) || 
			!IsValid(PlayerDicesOnTable[Slot]))
		{
			return nullptr;
		}
		for (const int32 Index : EnemyAvailableDices)
		{
			int32 Score = Strategy->ResultsScore(MaxResult, EnemyDices[Index]->Result());
			if (Score > BestResultScore)
			{
				BestResultScore = Score;
				BestResultIndex = Index;
			}
		}
		break;
	case EDicePlacementDecision::BlindPlacement:
		for (const int32 Index : EnemyAvailableDices)
		{
			int32 Score = Strategy->BlindScore(EnemyDices[Index]->Result());
			if (Score > BestResultScore)
			{
				BestResultScore = Score;
				BestResultIndex = Index;
			}
		}
		break;
	}

	if (BestResultIndex == INDEX_NONE)
	{
		return nullptr;
	}
	return EnemyDices[BestResultIndex];
}
