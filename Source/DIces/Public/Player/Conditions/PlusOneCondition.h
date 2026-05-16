// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCondition.h"
#include "PlusOneCondition.generated.h"


UCLASS()
class DICES_API UPlusOneCondition : public UBaseCondition
{
	GENERATED_BODY()

public:

	virtual void DrinkEffect() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
