

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JumpingDiceComponent.generated.h"

class ABaseEnemy;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UJumpingDiceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UJumpingDiceComponent();
	
	UFUNCTION(BlueprintCallable)
	void FakeDiceCheck(ABaseEnemy* Owner);
	
protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
