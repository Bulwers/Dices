// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCondition.h"
#include "LuckyDrinkCondition.generated.h"

//class UBaseDrinkWidget;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class DICES_API ULuckyDrinkCondition : public UBaseCondition
{
	GENERATED_BODY()

public:

	UPROPERTY()
	bool bCanRereoll;
	UPROPERTY()
	bool bHasRerolld;

	virtual void DrinkEffect() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
