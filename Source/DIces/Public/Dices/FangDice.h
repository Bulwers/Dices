// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDice.h"
#include "FangDice.generated.h"

/**
 * 
 */
UCLASS()
class DICES_API AFangDice : public ABaseDice
{
	GENERATED_BODY()
	
public:
	AFangDice();

	virtual int Result() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
