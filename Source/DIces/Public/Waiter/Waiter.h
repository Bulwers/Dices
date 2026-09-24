// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Waiter.generated.h"

class UCapsuleComponent;
class ABaseDrink;
class AGameStateBaseClass;

UCLASS()
class DICES_API AWaiter : public APawn
{
	GENERATED_BODY()

public:
	AWaiter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanDismiss;
	UFUNCTION(BlueprintCallable)
	void SetStartingLocAndRot();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> PlatePosition;

	UPROPERTY(EditAnywhere)
	FVector StartLoc;
	UPROPERTY(EditAnywhere)
	FRotator StartRot;

	UPROPERTY(EditAnywhere)
	FVector ServeLoc;
	UPROPERTY(EditAnywhere)
	FRotator ServeRot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<USceneComponent>> DrinkSpots;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> DrinkSpot_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> DrinkSpot_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> DrinkSpot_3;
	
	UFUNCTION(BlueprintCallable)
	void DrinkOffer();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseDrink>> DrinkToSpawn;
	UFUNCTION()
	void SpawnSelectedDrinks(const TArray<int32>& DrinksIndexes);


	// Index of drinks of specific lvl
	UPROPERTY(EditAnywhere)
	TArray<int32> DrinksLvl_1;
	UPROPERTY(EditAnywhere)
	TArray<int32> DrinksLvl_2;
	UPROPERTY(EditAnywhere)
	TArray<int32> DrinksLvl_3;

	// Shuffle drinks index
	TArray<int32> RandDrinks(const TArray<int32>& DrinksLvl);

	UPROPERTY(VisibleAnywhere)
	int32 DrinkTier;
	UPROPERTY()
	TObjectPtr<AGameStateBaseClass> GameState;

	// Chances for drinks of specific lvl
	UPROPERTY(EditAnywhere)
	int32 ChanceOfLvl_12;
	UPROPERTY(EditAnywhere)
	int32 ChanceOfLvl_123;
	UPROPERTY(EditAnywhere)
	int32 ChanceOfLvl_122;
	UPROPERTY(EditAnywhere)
	int32 ChanceOfLvl_113;

	// Drinks on plate
	
	UPROPERTY()
	TArray<TObjectPtr<ABaseDrink>> ActiveDrinks;
	
	UPROPERTY()
	TObjectPtr<ABaseDrink> Drink_1;
	UPROPERTY()
	TObjectPtr<ABaseDrink> Drink_2;
	UPROPERTY()
	TObjectPtr<ABaseDrink> Drink_3;

public:	

};
