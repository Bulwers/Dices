

#include "Dices/JumpingDice.h"

void AJumpingDice::DiceJump()
{
	RotateTime = 0;
	Rotation = GetActorRotation();
	DiceMesh->AddImpulse(FVector(0, 0, 1) * JumpForceValue(), NAME_None, false);
	RandRot = FMath::RandRange(-90, 90);
	GetWorldTimerManager().SetTimer(RotationTimerHandle, this, &AJumpingDice::DiceRotation, 0.1, true);
}

void AJumpingDice::DiceRotation()
{
	if (Result() == 6)
	{
		GetWorldTimerManager().ClearTimer(RotationTimerHandle);
		return;
	}
	SetActorRelativeRotation(FMath::Lerp(Rotation, FRotator(180, RandRot, 0), 0.8));
	++RotateTime;

	if (RotateTime >= 3)
	{
		GetWorldTimerManager().ClearTimer(RotationTimerHandle);
	}
}