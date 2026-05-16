// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DELEGATE(FOnDeathEffects);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION()
	void GetHit();

	UFUNCTION()
	int GetHealth() const { return Health; }

	FOnDeathEffects OnDeathEffects;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Health value
	UPROPERTY(EditAnywhere)
	int MaxHealth = 4;
	UPROPERTY(VisibleAnywhere)
	int Health;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
