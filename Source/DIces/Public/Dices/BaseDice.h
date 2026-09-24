

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDice.generated.h"

DECLARE_DELEGATE(FOnDiceStopped)

UCLASS()
class DICES_API ABaseDice : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseDice();

	FOnDiceStopped OnDiceStopped;
	
	UFUNCTION(BlueprintCallable)
	void PlayerRolling();

	UFUNCTION(BlueprintCallable)
	void EnemyRolling();

	UFUNCTION(BlueprintCallable)
	virtual int32 Result();
	UPROPERTY(VisibleAnywhere)
	int32 Bonus;
	UFUNCTION(BlueprintCallable)
	int32 Sum();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsEnemyChosen;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsChosen;
	UPROPERTY(BlueprintReadWrite)
	bool bIsPlayer;
	UPROPERTY(BlueprintReadWrite)
	bool bCanHighlight;
	UPROPERTY(BlueprintReadWrite)
	bool bIsRolled;
	
	UPROPERTY(VisibleAnywhere)
	bool bIsVisible;

	void StartLoc();
	UPROPERTY(EditAnywhere)
	float JumpForce;
	UPROPERTY(EditAnywhere)
	float JumpForceRange;
	float JumpForceValue();
	virtual void DiceJump();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsStopped;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> DiceMesh;

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Meta = (EditFixedSize))
	TArray<int32> DiceResults = { 0, 0, 0, 0, 0, 0};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class UArrowComponent>> Arrows;
	
	UPROPERTY(VisibleAnywhere)
	FVector Location;
	UPROPERTY(VisibleAnywhere)
	FVector StartLocation;
	UPROPERTY(VisibleAnywhere)
	FVector PastLoc;

	UPROPERTY(EditAnywhere)
	double DiceWeight;

	FTimerHandle PastPositionTimerHandle;
	FTimerHandle CurrentPositionTimerHandle;
	void CurrentPositionUpdate();
	void PastPositionUpdate();
	
public:	


};
