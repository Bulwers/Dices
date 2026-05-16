// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drinks/BaseDrink.h"
#include "Waiter.generated.h"

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
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* PlatePosition;

	UPROPERTY(EditAnywhere)
	FVector StartLoc;
	UPROPERTY(EditAnywhere)
	FRotator StartRot;

	UPROPERTY(EditAnywhere)
	FVector ServeLoc;
	UPROPERTY(EditAnywhere)
	FRotator ServeRot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* DrinkSpot_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* DrinkSpot_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* DrinkSpot_3;
	UFUNCTION(BlueprintCallable)
	void DrinkOffer();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseDrink>> DrinkToSpawn;
	UFUNCTION()
	void DrinkSpawn(int DrinkToSpawn_1, int DrinkToSpawn_2, int DrinkToSpawn_3);


	// Index of drinks of specific lvl
	UPROPERTY(EditAnywhere)
	TArray<int> DrinksLvl_1;
	UPROPERTY(EditAnywhere)
	TArray<int> DrinksLvl_2;
	UPROPERTY(EditAnywhere)
	TArray<int> DrinksLvl_3;

	// Shuffle drinks index
	UFUNCTION()
	FVector2D RandDrinks(TArray<int> DrinksLvl);

	UPROPERTY(VisibleAnywhere)
	int DrinkTier;
	UPROPERTY()
	class AGameStateBaseClass* GameState;

	// Chances for drinks of specific lvl
	UPROPERTY(EditAnywhere)
	int ChanceOfLvl_12;
	UPROPERTY(EditAnywhere)
	int ChanceOfLvl_123;
	UPROPERTY(EditAnywhere)
	int ChanceOfLvl_122;
	UPROPERTY(EditAnywhere)
	int ChanceOfLvl_113;

	// Drinks on plate
	UPROPERTY()
	ABaseDrink* Drink_1;
	UPROPERTY()
	ABaseDrink* Drink_2;
	UPROPERTY()
	ABaseDrink* Drink_3;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
