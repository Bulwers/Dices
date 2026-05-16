// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCondition.h"
#include "223455DiceCondition.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class DICES_API U223455DiceCondition : public UBaseCondition
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ABaseDice*> PlayerDices;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<ABaseDice> TempDiceToSpawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ABaseDice*> TempDices;

	virtual void DrinkEffect() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
