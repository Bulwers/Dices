// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dices/BaseDice.h"
#include "GameFramework/Pawn.h"
#include "BasePlayer.generated.h"

DECLARE_MULTICAST_DELEGATE(FDiceRolling)
DECLARE_DELEGATE_OneParam(FDicePlacement, ABaseDice*)

UENUM(BlueprintType)
enum class ECamPosition : uint8
{
	Top		UMETA(DisplayName = "Top"),
	Left	UMETA(DisplayName = "Left"),
	Right	UMETA(DisplayName = "Right"),
	Bottom	UMETA(DisplayName = "Bottom"),
	Waiter	UMETA(DisplayName = "Waiter")
};

UCLASS()
class DICES_API ABasePlayer : public APawn
{
	GENERATED_BODY()

public:
	ABasePlayer();

	FDiceRolling OnDiceRolled;
	FDicePlacement OnDicePlacement;

	UFUNCTION()
	void PlayerDeath();

	UFUNCTION(BlueprintCallable)
	void DicesTest(ABaseDice* Dice);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<int> TestResults;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ABaseDice>> PlayerDices;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ABaseDice>> PlayerDicesOnHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ABaseDice>> PlayerDicesOnTable;
	
	UFUNCTION()
	void ResetDicesPosition();

	UPROPERTY(EditAnywhere, Category = "Drinks")
	TArray<FVector> DrinksOnTable;

	UPROPERTY(VisibleAnywhere)
	TArray<bool> bIsDrinkSpotTaken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UHealthComponent> HealthComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UPlayerCameraManagerComponent> CameraComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UPlayerDiceManagerComponent> DiceComp;

	UFUNCTION()
	void GetHit() const;
	UFUNCTION()
	int GetHealth() const;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<class UBaseCondition>> DrinkConditions;

	UFUNCTION(BlueprintCallable)
	void FangSpawn();

	UFUNCTION()
	void DestroyFangsOnTable();

	// Gold
	UFUNCTION(BlueprintCallable)
	void AddGold();
	UFUNCTION(BlueprintCallable)
	void RemoveGold(int Amount);
	UFUNCTION(BlueprintCallable)
	void ShowCoins();
	UFUNCTION(BlueprintCallable)
	int GetGoldQuantity();

	bool bWasTableHit = false;
	int TableHitCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bPlusOneBuff = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bPlusTwoBuff = false;

	UFUNCTION(BlueprintCallable)
	void MoveCamera(ECamPosition Direction);
	UFUNCTION()
	void Set_bCanChooseDiceForBrawl(bool Value);
	UFUNCTION()
	void Set_bCanMove(bool Value);
	UFUNCTION()
	void Set_bPlayerDiceRolled(bool Value);
	UFUNCTION()
	bool Get_bPlayerDiceRolled();
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UCameraComponent> Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> CameraPosition;
	TWeakObjectPtr<APlayerController> Controller;

private:
	
	UPROPERTY(EditAnywhere)
	float MoveTime;
	UPROPERTY(EditAnywhere)
	float MoveSpeed;

	UPROPERTY(VisibleAnywhere)
	int GoldQuantity = 0;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGold> GoldToSpawn;
	UPROPERTY(EditAnywhere)
	FVector GoldSpawnLocation;
	UPROPERTY(EditAnywhere)
	FRotator GoldSpawnRotation;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFangDice> FangToSpawn;
	UPROPERTY(EditDefaultsOnly)
	FVector PlayerFangSpawnLoc;
	UPROPERTY(EditDefaultsOnly)
	FRotator PlayerFangSpawnRot;

	UFUNCTION()
	void Pressed_W();
	UFUNCTION()
	void Pressed_S();
	UFUNCTION()
	void Pressed_A();
	UFUNCTION()
	void Pressed_D();
	UFUNCTION()
	void HandleCamera(ECamPosition Direction, bool CanHighlight, bool DiceRolledRequired);

	void DiceChoose();
	void DiceRolling();
	void ResetDiceForHand();
	void TableHit();

	UFUNCTION()
	void BooleanReset();

	UFUNCTION()
	FVector RandLoc(FVector Loc, int Range);
	UFUNCTION()
	FRotator RandRot(FRotator Rot, int Range);

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
