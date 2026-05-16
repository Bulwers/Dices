// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chopper.generated.h"

UCLASS()
class DICES_API AChopper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChopper();
	
	UPROPERTY(VisibleAnywhere)
	class ABasePlayer* PlayerCharacter;
	
	UPROPERTY(VisibleAnywhere)
	class ABaseEnemy* EnemyCharacter;
	
	UPROPERTY(VisibleAnywhere)
	class AGameStateBaseClass* GameState;
	
	UFUNCTION(BlueprintCallable)
	void ChopperHit(int DicesToRemove);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
