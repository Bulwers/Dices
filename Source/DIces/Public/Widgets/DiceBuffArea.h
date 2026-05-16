// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/BasePlayer.h"
#include "GameFramework/Actor.h"
#include "BuffTriggerAreaComponent.h"
#include "DiceBuffArea.generated.h"

UCLASS()
class DICES_API ADiceBuffArea : public AActor
{
	GENERATED_BODY()
	
public:	
	ADiceBuffArea();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABasePlayer* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBuffTriggerAreaComponent* TriggerArea;

	UFUNCTION()
	void DiceBuff(AActor* ActorClicked, FKey InKey);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
