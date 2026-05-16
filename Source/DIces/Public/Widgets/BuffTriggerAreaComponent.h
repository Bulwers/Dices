// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "BuffTriggerAreaComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DICES_API UBuffTriggerAreaComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	UBuffTriggerAreaComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ABaseDice* PlayerDice;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};