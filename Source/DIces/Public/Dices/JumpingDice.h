

#pragma once

#include "CoreMinimal.h"
#include "BaseDice.h"
#include "JumpingDice.generated.h"


UCLASS()
class DICES_API AJumpingDice : public ABaseDice
{
	GENERATED_BODY()
	
public:

	virtual void DiceJump() override;
	
protected:
	
	FTimerHandle RotationTimerHandle;
	void DiceRotation();

	float RotateTime = 0;
	FRotator Rotation;
	int RandRot;
};
