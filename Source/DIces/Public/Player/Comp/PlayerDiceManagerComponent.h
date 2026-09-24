// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerDiceManagerComponent.generated.h"

class ABasePlayer;
class ABaseDice;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UPlayerDiceManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UPlayerDiceManagerComponent();
	
	UFUNCTION()
	void DiceChoose(ECamPosition CurrentCamPos, APlayerController* PlayerController, ABasePlayer* Player);
	UFUNCTION()
	void DiceRolling(ECamPosition CurrentCamPos, ABasePlayer* Player);
	UFUNCTION()
	void ResetDiceForHand(ECamPosition CurrentCamPos, ABasePlayer* Player);
	UFUNCTION()
	void ResetDicesPosition(ABasePlayer* Player);
	UFUNCTION()
	void DiceHighlight(bool bValue, ABasePlayer* Player);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseDice> DiceToSpawn;

	UPROPERTY(EditAnywhere)
	FVector DiceSpawnLoc;

	UPROPERTY(EditAnywhere)
	FRotator DiceSpawnRot;

	UPROPERTY(VisibleAnywhere)
	bool bCanChooseDiceForHand = false;

	UPROPERTY(VisibleAnywhere)
	bool bCanChooseDiceForBrawl = false;

	UPROPERTY(BlueprintReadWrite)
	bool bPlayerDiceRolled = false;

	UPROPERTY()
	bool bAreDicesSpawned = false;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FVector> DiceSpots;

	UFUNCTION()
	FVector RandLoc(FVector Loc, int32 Range);
	UFUNCTION()
	FRotator RandRot(FRotator Rot, int32 Range);
};
