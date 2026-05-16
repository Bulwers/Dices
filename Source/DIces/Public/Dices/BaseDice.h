

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
	virtual int Result();
	UPROPERTY(VisibleAnywhere)
	int Bonus;
	UFUNCTION(BlueprintCallable)
	int Sum();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsEnemyChoosen;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsChoosen;
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
	UStaticMeshComponent* DiceMesh;

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Meta = (EditFixedSize))
	TArray<int> DiceResults = { 0, 0, 0, 0, 0, 0};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UArrowComponent*> Arrows;
	
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

	virtual void Tick(float DeltaTime) override;

};
