
#pragma once

#include "CoreMinimal.h"
#include "BaseCondition.h"
#include "LuckyDrinkCondition.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class DICES_API ULuckyDrinkCondition : public UBaseCondition
{
	GENERATED_BODY()

public:

	UPROPERTY()
	bool bCanReroll;
	UPROPERTY()
	bool bHasRerolled;

	virtual void DrinkEffect() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
