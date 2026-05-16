// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/BasePlayer.h"
#include "Game/GameStateBaseClass.h"
#include "BaseCondition.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class DICES_API UBaseCondition : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseCondition();

	UFUNCTION()
	virtual void DrinkEffect();
	UPROPERTY()
	bool bCanBuff;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	AGameStateBaseClass* GameState;

	// Player character
	UPROPERTY(VisibleAnywhere)
	ABasePlayer* Player;

	// Lifetime starting turn
	UPROPERTY(VisibleAnywhere)
	int StartTurnCount;
	// Actual turn
	UPROPERTY(VisibleAnywhere)
	int ActualTurnCount;
	UPROPERTY(VisibleAnywhere)
	int NewTurnCount;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
