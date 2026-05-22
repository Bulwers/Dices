

#include "Enemies/Comp/BigEnemyDecisionComponent.h"
#include "Dices/BaseDice.h"
#include "Enemies/EnemyStrategy.h"


ABaseDice* UBigEnemyDecisionComponent::ChoosingDiceToPutOnTable(
	const TArray<ABaseDice*>& PlayerDicesOnTable, 
	const TArray<ABaseDice*>& EnemyDices, 
	const int Slot)
{
	const int PlayerFirst = PlayerDicesOnTable[Slot] ? PlayerDicesOnTable[Slot]->Result() : 0;
	const int PlayerSecond = (Slot + 1 < PlayerDicesOnTable.Num() && PlayerDicesOnTable[Slot + 1]) ? PlayerDicesOnTable[Slot + 1]->Result() : 0;
	const int MaxResult = FMath::Max(PlayerFirst, PlayerSecond);
	
	int BestResultScore = -1;
	int BestResultIndex = -1;
	
	TArray<int> EnemyAvailableDices;
	for (int i = 0; i < EnemyDices.Num(); i++)
	{
		if (IsValid(EnemyDices[i]) && !EnemyDices[i]->bIsEnemyChoosen)
		{
			EnemyAvailableDices.Add(i);
		}
	}
	
	switch (EEnemyPlacementDecision)
	{
	case EDicePlacementDecision::KnowingPlacement:
		for (const int Index : EnemyAvailableDices)
		{
			int Score = Strategy->ResultsScore(MaxResult, EnemyDices[Index]->Result());
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
