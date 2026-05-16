// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/BaseEnemy.h"
#include "Chef.generated.h"

/**
 * 
 */
UCLASS()
class DICES_API AChef : public ABaseEnemy
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void DiceCheckForHit();
	
	//virtual void EnemyChoosingDice() override;
	UPROPERTY(EditAnywhere)
	FVector ChopperLoc;
	UPROPERTY(EditAnywhere)
	FRotator ChopperRot;
	UPROPERTY(BlueprintReadWrite)
	class AChopper* Chopper;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChopper> ChopperToSpawn;
	UFUNCTION(BlueprintCallable)
	void ChopperSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};
