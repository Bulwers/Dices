// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrategyScoreData.h"
#include "EnemyStrategy.generated.h"

UCLASS()
class DICES_API UEnemyStrategy : public UObject
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION()
	void InitNameAndData(FName Name);
	UFUNCTION(BlueprintCallable)
	virtual int ResultsScore(const int PlayerResult, const int EnemyResult);
	UFUNCTION(BlueprintCallable)
	virtual int BlindScore(const int EnemyResult);
	
	
private:
	
	UPROPERTY()
	FName StrategyName;
	UPROPERTY()
	UDataTable* StrategyScoreDataTable;
	FStrategyScoreData* Data;
};
