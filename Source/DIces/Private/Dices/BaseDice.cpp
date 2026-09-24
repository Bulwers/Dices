

#include "Dices/BaseDice.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"

ABaseDice::ABaseDice()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("Dice"));

	DiceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DiceMesh"));
	RootComponent = DiceMesh;

	for (int32 i = 0; i < 6; i++)
	{
		UArrowComponent* Arrow= CreateDefaultSubobject<UArrowComponent>(*FString::Printf(TEXT("Arrow%d"), i+1));
		Arrow->SetupAttachment(DiceMesh);
		Arrows.Add(Arrow);
	}
}

void ABaseDice::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	bIsPlayer = false;
	bIsChosen = false;
	bIsEnemyChosen = false;
	bCanHighlight = false;
	bIsRolled = false;
	bIsStopped = true;
	bIsVisible = true;
	
	Bonus = 0;
}

void ABaseDice::CurrentPositionUpdate()
{
	Location = GetActorLocation();

	if (Location.Equals(PastLoc, 0.5f))
	{
		bIsStopped = true;
		OnDiceStopped.ExecuteIfBound();
		GetWorldTimerManager().ClearTimer(CurrentPositionTimerHandle);
		GetWorldTimerManager().ClearTimer(PastPositionTimerHandle);
	}
	else bIsStopped = false;
}

void ABaseDice::PastPositionUpdate()
{
	PastLoc = GetActorLocation();
}

void ABaseDice::StartLoc()
{
	SetActorLocation(StartLocation, false, nullptr, ETeleportType::None);
	bIsRolled = false;
}

void ABaseDice::PlayerRolling()
{
	float Loc_X = FMath::RandRange(-140, -120);
	float Loc_Y = FMath::RandRange(60, 80);
	float Loc_Z = FMath::RandRange(110, 120);
	FVector SpawnLoc(Loc_X, Loc_Y, Loc_Z);
	float Rot_X = FMath::RandRange(0, 60);
	float Rot_Y = FMath::RandRange(-30, 0);
	float Rot_Z = FMath::RandRange(0, 45);
	FRotator SpawnRot(Rot_X, Rot_Y, Rot_Z);
	DiceMesh->SetWorldLocationAndRotation(SpawnLoc, SpawnRot, false, nullptr, ETeleportType::None);
	FVector ForwardVector = (GetActorForwardVector() * 150 * DiceWeight);
	DiceMesh->AddImpulse(ForwardVector, NAME_None, false);

	GetWorldTimerManager().SetTimer(CurrentPositionTimerHandle, this, &ABaseDice::CurrentPositionUpdate, 0.155, true);
	GetWorldTimerManager().SetTimer(PastPositionTimerHandle, this, &ABaseDice::PastPositionUpdate, 1, true, 1);

	Bonus = 0;
}

void ABaseDice::EnemyRolling()
{
	float Loc_X = FMath::RandRange(120, 140);
	float Loc_Y = FMath::RandRange(-80, -60);
	float Loc_Z = FMath::RandRange(110, 120);
	FVector SpawnLoc(Loc_X, Loc_Y, Loc_Z);
	float Rot_X = FMath::RandRange(-60, 0);
	float Rot_Y = FMath::RandRange(-30, 0);
	float Rot_Z = FMath::RandRange(0, 45);
	FRotator SpawnRot(Rot_X, Rot_Y, Rot_Z);
	DiceMesh->SetWorldLocationAndRotation(SpawnLoc, SpawnRot, false, nullptr, ETeleportType::None);
	FVector ForwardVector = (GetActorForwardVector() * 150 * DiceWeight)*(-1);
	DiceMesh->AddImpulse(ForwardVector, NAME_None, false);

	GetWorldTimerManager().SetTimer(CurrentPositionTimerHandle, this, &ABaseDice::CurrentPositionUpdate, 0.155, true);
	GetWorldTimerManager().SetTimer(PastPositionTimerHandle, this, &ABaseDice::PastPositionUpdate, 1, true, 1);

	Bonus = 0;
}

int ABaseDice::Result()
{
	const int32 FacesNum = FMath::Min(Arrows.Num(), DiceResults.Num());
	for (int32 i = 0; i < FacesNum; i++)
	{
		if (Arrows[i] && Arrows[i]->GetForwardVector().Z > 0.5f)
		{
			return DiceResults[i];
		}
	}
	return 0;
}

float ABaseDice::JumpForceValue()
{
	float ForceResult = FMath::RandRange(JumpForce - JumpForceRange, JumpForce + JumpForceRange);

	return ForceResult;
}

void ABaseDice::DiceJump()
{
	DiceMesh->AddImpulse(FVector(0, 0, 1) * JumpForceValue(), NAME_None, false);
}

int ABaseDice::Sum()
{
	return (Result() + Bonus);
}