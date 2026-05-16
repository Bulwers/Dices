

#include "Player/Comp/PlayerCameraManagerComponent.h"
#include "Player/BasePlayer.h"

UPlayerCameraManagerComponent::UPlayerCameraManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerCameraManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerCameraManagerComponent::Initialize(USceneComponent* InCameraPosition, float InMoveSpeed, float InMoveTime)
{
	CameraPosition = InCameraPosition;
	CameraPos = CameraPosition->GetComponentLocation();
	CameraRot = CameraPosition->GetComponentRotation();
	MoveSpeed = InMoveSpeed;
	MoveTime = InMoveTime;
	ECurrentCamPos = ECamPosition::Bottom;
}

void UPlayerCameraManagerComponent::MoveCamera(ECamPosition Direction)
{
	CurrentMoveTime = 0;
	switch (Direction)
	{
	case ECamPosition::Top:
		GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &UPlayerCameraManagerComponent::MoveTop, 0.01f, true);
		ECurrentCamPos = ECamPosition::Top;
		OnCameraTop.Broadcast();
		break;
	case ECamPosition::Bottom:
		GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &UPlayerCameraManagerComponent::MoveBottom, 0.01f, true);
		ECurrentCamPos = ECamPosition::Bottom;
		OnCameraBottom.Broadcast();
		break;
	case ECamPosition::Left:
		GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &UPlayerCameraManagerComponent::MoveLeft, 0.01f, true);
		ECurrentCamPos = ECamPosition::Left;
		OnCameraLeft.Broadcast();
		break;
	case ECamPosition::Right:
		GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &UPlayerCameraManagerComponent::MoveRight, 0.01f, true);
		ECurrentCamPos = ECamPosition::Right;
		OnCameraRight.Broadcast();
		break;
	case ECamPosition::Waiter:
		bCanMove = false;
		GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &UPlayerCameraManagerComponent::MoveOnWaiter, 0.01f, true);
		ECurrentCamPos = ECamPosition::Waiter;
		OnCameraWaiter.Broadcast();
		break;
	}
}

void UPlayerCameraManagerComponent::MoveTop()
{
	FRotator NewRotation = CameraRot + FRotator(-60, 0, 0);
	CameraPosition->SetWorldRotation(FMath::RInterpTo(CameraPosition->GetComponentRotation(), NewRotation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	FVector NewLocation = CameraPos + FVector(140, 0, 0);
	CameraPosition->SetWorldLocation(FMath::VInterpTo(CameraPosition->GetComponentLocation(), NewLocation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	if (++CurrentMoveTime >= MoveTime)
		GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
}

void UPlayerCameraManagerComponent::MoveBottom()
{
	CameraPosition->SetWorldRotation(FMath::RInterpTo(CameraPosition->GetComponentRotation(), CameraRot, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	CameraPosition->SetWorldLocation(FMath::VInterpTo(CameraPosition->GetComponentLocation(), CameraPos, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	if (++CurrentMoveTime >= MoveTime)
		GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
}

void UPlayerCameraManagerComponent::MoveLeft()
{
	FRotator NewRotation = CameraRot + FRotator(10, -40, 0);
	CameraPosition->SetWorldRotation(FMath::RInterpTo(CameraPosition->GetComponentRotation(), NewRotation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	FVector NewLocation = CameraPos + FVector(0, 0, -20);
	CameraPosition->SetWorldLocation(FMath::VInterpTo(CameraPosition->GetComponentLocation(), NewLocation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	if (++CurrentMoveTime >= MoveTime)
		GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
}

void UPlayerCameraManagerComponent::MoveRight()
{
	FRotator NewRotation = CameraRot + FRotator(-40, 40, 0);
	CameraPosition->SetWorldRotation(FMath::RInterpTo(CameraPosition->GetComponentRotation(), NewRotation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	FVector NewLocation = CameraPos + FVector(40, 30, 0);
	CameraPosition->SetWorldLocation(FMath::VInterpTo(CameraPosition->GetComponentLocation(), NewLocation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	if (++CurrentMoveTime >= MoveTime)
		GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
}

void UPlayerCameraManagerComponent::MoveOnWaiter()
{
	FRotator NewRotation = CameraRot + FRotator(10, -100, 0);
	CameraPosition->SetWorldRotation(FMath::RInterpTo(CameraPosition->GetComponentRotation(), NewRotation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	FVector NewLocation = CameraPos + FVector(0, -20, 0);
	CameraPosition->SetWorldLocation(FMath::VInterpTo(CameraPosition->GetComponentLocation(), NewLocation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	if (++CurrentMoveTime >= MoveTime)
		GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
}
