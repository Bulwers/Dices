// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "BaseOgreEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DICES_API ABaseOgreEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:

	// Enemy rolling dices
	//virtual void EnemyDiceRolling() override;
	// Spawning enemy dices
	//virtual void EnemySpawnDices() override;

	virtual void DeathAction() override;

	// Enemy choosing dices for brawl
	//virtual void EnemyChoosingDice() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
