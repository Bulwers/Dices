
#pragma once

#include "CoreMinimal.h"
#include "BaseCondition.h"
#include "223455DiceCondition.generated.h"

class ABaseDice;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class DICES_API U223455DiceCondition : public UBaseCondition
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ABaseDice*> PlayerDices;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<ABaseDice> TempDiceToSpawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ABaseDice*> TempDices;

	virtual void DrinkEffect() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
