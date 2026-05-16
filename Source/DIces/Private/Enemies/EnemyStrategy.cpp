// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyStrategy.h"

void UEnemyStrategy::InitNameAndData(FName Name)
{
	StrategyName = Name;
	StrategyScoreDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Dynamic/Enemies/StrategyTable.StrategyTable"));
	Data = StrategyScoreDataTable->FindRow<FStrategyScoreData>(StrategyName, TEXT(""));
}

int UEnemyStrategy::ResultsScore(const int PlayerResult, const int EnemyResult)
{
	if (!StrategyScoreDataTable) return 0;
	
	int Difference =  FMath::Clamp(EnemyResult - PlayerResult, -5, 5);
	
	switch (FMath::Clamp(Difference, -5, 5))
	{
	case  5: return Data->Diff_Plus_5;
	case  4: return Data->Diff_Plus_4;
	case  3: return Data->Diff_Plus_3;
	case  2: return Data->Diff_Plus_2;
	case  1: return Data->Diff_Plus_1;
	case  0: return Data->Diff_0;
	case -1: return Data->Diff_Minus_1;
	case -2: return Data->Diff_Minus_2;
	case -3: return Data->Diff_Minus_3;
	case -4: return Data->Diff_Minus_4;
	case -5: return Data->Diff_Minus_5;
	default: return 0;
	}
}

int UEnemyStrategy::BlindScore(const int EnemyResult)
{
	switch (EnemyResult)
	{
	case 6: return Data->Blind_6;
	case 5: return Data->Blind_5;
	case 4: return Data->Blind_4;
	case 3: return Data->Blind_3;
	case 2: return Data->Blind_2;
	case 1: return Data->Blind_1;
	default: return 0;
	}
}
