

#include "Player/BasePlayer.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/HealthComponent.h"
#include "Player/Conditions/BaseCondition.h"
#include "Dices/FangDice.h"
#include "Misc/Gold.h"
#include "Math/UnrealMathUtility.h"
#include "Player/Comp/PlayerCameraManagerComponent.h"
#include "Player/Comp/PlayerDiceManagerComponent.h"
#include "GameFramework/PlayerController.h"

ABasePlayer::ABasePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComponent;

	CameraPosition = CreateDefaultSubobject<USceneComponent>(TEXT("CameraPosition"));
	CameraPosition->SetupAttachment(CapsuleComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraPosition);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	CameraComp = CreateDefaultSubobject<UPlayerCameraManagerComponent>(TEXT("CameraComp"));
	DiceComp = CreateDefaultSubobject<UPlayerDiceManagerComponent>(TEXT("DiceComp"));
	
	DrinksOnTable.Init(FVector(0, 0, 0), 6);
	DrinkConditions.Init(nullptr, 6);
	bIsDrinkSpotTaken.Init(false, 6);
	PlayerDices.Init(nullptr, 12);
	PlayerDicesOnHand.Init(nullptr, 6);
	PlayerDicesOnTable.Init(nullptr, 6);
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	HealthComp->OnDeathEffects.BindUObject(this, &ABasePlayer::PlayerDeath);

	Controller = Cast<APlayerController>(GetController());
	if (Controller)
	{
		Controller->SetShowMouseCursor(true);
	}

	CameraComp->Initialize(CameraPosition, MoveSpeed, MoveTime);
}

void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePlayer::DicesTest(ABaseDice* Dice)
{
	if (Dice)
	{
		Dice->PlayerRolling();
		Dice->bIsRolled = true;
	}
}

void ABasePlayer::PlayerDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Death"))
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Move Top"),    IE_Pressed, this, &ABasePlayer::Pressed_W);
	PlayerInputComponent->BindAction(TEXT("Move Bottom"), IE_Pressed, this, &ABasePlayer::Pressed_S);
	PlayerInputComponent->BindAction(TEXT("Move Left"),   IE_Pressed, this, &ABasePlayer::Pressed_A);
	PlayerInputComponent->BindAction(TEXT("Move Right"),  IE_Pressed, this, &ABasePlayer::Pressed_D);
	PlayerInputComponent->BindAction(TEXT("Mouse Click"), IE_Pressed, this, &ABasePlayer::DiceChoose);
	PlayerInputComponent->BindAction(TEXT("Dice Rolling"),IE_Pressed, this, &ABasePlayer::DiceRolling);
	PlayerInputComponent->BindAction(TEXT("Choose Dice"), IE_Pressed, this, &ABasePlayer::ResetDiceForHand);
	PlayerInputComponent->BindAction(TEXT("Hit Table"),   IE_Pressed, this, &ABasePlayer::TableHit);
}

void ABasePlayer::BooleanReset()
{
	bPlusOneBuff = false;
	bPlusTwoBuff = false;
}

void ABasePlayer::Set_bCanChooseDiceForBrawl(bool bValue)
{
	DiceComp->bCanChooseDiceForBrawl = bValue;
}

void ABasePlayer::Set_bCanMove(bool bValue)
{
	CameraComp->bCanMove = bValue;
}

void ABasePlayer::Set_bPlayerDiceRolled(bool bValue)
{
	DiceComp->bPlayerDiceRolled = bValue;
}

bool ABasePlayer::Get_bPlayerDiceRolled()
{
	return DiceComp->bPlayerDiceRolled;
}

// ========================
// CAMERA
// ========================

void ABasePlayer::MoveCamera(ECamPosition Direction)
{
	CameraComp->MoveCamera(Direction);
}

void ABasePlayer::Pressed_W()
{
	HandleCamera(ECamPosition::Top, false, true);
}

void ABasePlayer::Pressed_S()
{
	HandleCamera(ECamPosition::Bottom, false, false);
}

void ABasePlayer::Pressed_A()
{
	HandleCamera(ECamPosition::Left, false, false);
}

void ABasePlayer::Pressed_D()
{
	HandleCamera(ECamPosition::Right, true, false);
}

void ABasePlayer::HandleCamera(ECamPosition Direction, bool CanHighlight, bool DiceRolledRequired)
{
	if (!CameraComp->bCanMove) return;
	if (DiceRolledRequired && !DiceComp->bPlayerDiceRolled) return;
	
	MoveCamera(Direction);
	BooleanReset();
	DiceComp->DiceHighlight(CanHighlight, this);
}

// ========================
// DICE
// ========================

void ABasePlayer::DiceChoose()
{
	const auto CamPosition = CameraComp->GetCurrentCamPos();
	DiceComp->DiceChoose(CamPosition, Controller, this);

	// Auto-move to top after placing last dice on table
	if (CamPosition == ECamPosition::Right && PlayerDicesOnTable[5])
	{
		CameraComp->MoveCamera(ECamPosition::Top);
	}
}

void ABasePlayer::DiceRolling()
{
	DiceComp->DiceRolling(CameraComp->GetCurrentCamPos(), this);
}

void ABasePlayer::ResetDiceForHand()
{
	DiceComp->ResetDiceForHand(CameraComp->GetCurrentCamPos(), this);
}

void ABasePlayer::ResetDicesPosition()
{
	DiceComp->ResetDicesPosition(this);
}

void ABasePlayer::TableHit()
{
	for (ABaseDice* Dice : PlayerDicesOnTable)
	{
		if (IsValid(Dice) && Dice->bIsStopped)
		{
			Dice->DiceJump();
		}
	}
	bWasTableHit = true;
	++TableHitCount;
}

void ABasePlayer::DestroyFangsOnTable()
{
	static const FName Tag(TEXT("Fang"));
	for (ABaseDice*& Dice : PlayerDicesOnTable)
	{
		if (IsValid(Dice) && Dice->ActorHasTag(Tag))
		{
			Dice->Destroy();
			Dice = nullptr;
		}
	}
}

// ========================
// GOLD
// ========================

void ABasePlayer::AddGold()
{
	GoldQuantity++;
}

void ABasePlayer::RemoveGold(int Amount)
{
	GoldQuantity -= Amount;
	if (GoldQuantity < 0) GoldQuantity = 0;
}

void ABasePlayer::ShowCoins()
{
	if (GoldQuantity <= 0) return;
	for (int i = 1; i <= GoldQuantity; i++)
	{
		GetWorld()->SpawnActor<AGold>(GoldToSpawn, RandLoc(GoldSpawnLocation, 5), RandRot(GoldSpawnRotation, 5));
	}
}

int ABasePlayer::GetGoldQuantity()
{
	return GoldQuantity;
}

// ========================
// MISC
// ========================

void ABasePlayer::FangSpawn()
{
	GetWorld()->SpawnActor<AFangDice>(FangToSpawn, RandLoc(PlayerFangSpawnLoc, 3), RandRot(PlayerFangSpawnRot, 20));
}

void ABasePlayer::GetHit() const
{
	HealthComp->GetHit();
}

int ABasePlayer::GetHealth() const
{
	return HealthComp->GetHealth();
}

FVector ABasePlayer::RandLoc(FVector Loc, int Range)
{
	float X = FMath::RandRange(Loc.X - Range, Loc.X + Range);
	float Y = FMath::RandRange(Loc.Y - Range, Loc.Y + Range);
	float Z = FMath::RandRange(Loc.Z - Range, Loc.Z + Range);
	return FVector(X, Y, Z);
}

FRotator ABasePlayer::RandRot(FRotator Rot, int Range)
{
	float Roll  = FMath::RandRange(Rot.Roll  - Range, Rot.Roll  + Range);
	float Pitch = FMath::RandRange(Rot.Pitch - Range, Rot.Pitch + Range);
	float Yaw   = FMath::RandRange(Rot.Yaw   - Range, Rot.Yaw   + Range);
	return FRotator(Roll, Pitch, Yaw);
}