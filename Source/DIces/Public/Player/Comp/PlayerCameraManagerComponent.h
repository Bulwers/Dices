// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCameraManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraMovement);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UPlayerCameraManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerCameraManagerComponent();

	void Initialize(USceneComponent* InCameraPosition, float InMoveSpeed, float InMoveTime);

	void MoveCamera(ECamPosition Direction);

	UFUNCTION(BlueprintCallable)
	ECamPosition GetCurrentCamPos() const { return ECurrentCamPos; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanMove = false;
	
	UPROPERTY(BlueprintAssignable)
	FOnCameraMovement OnCameraTop;
	UPROPERTY(BlueprintAssignable)
	FOnCameraMovement OnCameraBottom;
	UPROPERTY(BlueprintAssignable)
	FOnCameraMovement OnCameraLeft;
	UPROPERTY(BlueprintAssignable)
	FOnCameraMovement OnCameraRight;
	UPROPERTY(BlueprintAssignable)
	FOnCameraMovement OnCameraWaiter;
	

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	USceneComponent* CameraPosition;
	
	UPROPERTY(VisibleAnywhere)
	ECamPosition ECurrentCamPos;

	FVector CameraPos;
	FRotator CameraRot;

	FTimerHandle MoveTimerHandle;
	float CurrentMoveTime = 0;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 5.f;

	UPROPERTY(EditAnywhere)
	float MoveTime = 30.f;

	void MoveTop();
	void MoveBottom();
	void MoveLeft();
	void MoveRight();
	void MoveOnWaiter();
};
