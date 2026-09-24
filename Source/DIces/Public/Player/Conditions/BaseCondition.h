
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCondition.generated.h"

class AGameStateBaseClass;
class ABasePlayer;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class DICES_API UBaseCondition : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseCondition();

	UFUNCTION()
	virtual void DrinkEffect();
	UPROPERTY()
	bool bCanBuff;
	
	UPROPERTY(VisibleAnywhere)
	int32 TurnLifetime;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	AGameStateBaseClass* GameState;

	UPROPERTY(VisibleAnywhere)
	ABasePlayer* Player;

	UPROPERTY(VisibleAnywhere)
	int32 StartTurnCount;

	UPROPERTY(VisibleAnywhere)
	int32 ActualTurnCount;
	UPROPERTY(VisibleAnywhere)
	int32 NewTurnCount;
	

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
