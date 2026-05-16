

#include "Enemies/BaseEnemy.h"
#include "Player/BasePlayer.h"
#include "DialogueSystem/DialogueManager.h"
#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Algo/AllOf.h"
#include "Enemies/Comp/EnemyDecisionComponent.h"
#include "Enemies/Comp/EnemyDiceComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyHealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	EnemyDecisionComp = CreateDefaultSubobject<UEnemyDecisionComponent>(TEXT("EnemyDecisionComp"));
	EnemyDiceComp = CreateDefaultSubobject<UEnemyDiceComponent>(TEXT("EnemyDiceComp"));
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		Player->OnDiceRolled.AddUObject(this, &ABaseEnemy::EnemyDiceRolling);
	}
	EnemyHealthComp->OnDeathEffects.BindUObject(this, &ABaseEnemy::DeathAction);
	DialogueManager = Cast<ADialogueManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ADialogueManager::StaticClass()));
	if (!DialogueManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueManager not found"));
	}
	
	EnemyDicesOnHand.Init(nullptr, DicesToSpawn.Num());
	EnemyDicesOnTable.Init(nullptr, 6);
	PlayerDicesOnTable.Init(nullptr, 6);

	bEnemyDiceRolled = false;
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEnemy::DeathAction()
{
	for (ABaseDice* Dice : EnemyDicesOnHand)
	{
		if (IsValid(Dice)) Dice->Destroy();
	}
	UE_LOG(LogTemp, Warning, TEXT("Enemy Death Effects Execute"));
	EnemyDiedDelegate.ExecuteIfBound();
	this->Destroy();
}

void ABaseEnemy::GetHit() const
{
	EnemyHealthComp->GetHit();
}

void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseEnemy::EnemySpawnDices()
{
	EnemyDiceComp->SpawnDices(EnemyDicesOnHand, DicesToSpawn, this);
}

void ABaseEnemy::EnemyDiceRolling()
{
	if (bEnemyDiceRolled) return;
	if (!Algo::AllOf(EnemyDicesOnHand, [](ABaseDice* Dice) { return Dice != nullptr; })) return;
	for (ABaseDice* Dice : EnemyDicesOnHand)
	{
		Dice->EnemyRolling();
		Dice->bIsEnemyChoosen = false;
	}
	bEnemyDiceRolled = true;
	bAreAllDicesStopped = false;
}

void ABaseEnemy::PlaceDiceOnTable()
{
	int Spot = EnemyDecisionComp->FindSlotToPlaceDice(PlayerDicesOnTable, EnemyDicesOnTable);
	const TArray Spots = {
		FVector(5, -25, 98),
		FVector(5, -15, 98),
		FVector(5, -5, 98),
		FVector(5, 5, 98),
		FVector(5, 15, 98),
		FVector(5, 25, 98)
	};
	ABaseDice* Dice = EnemyDecisionComp->ChoosingDiceToPutOnTable(PlayerDicesOnTable, EnemyDicesOnTable, EnemyDicesOnHand);
	if (!Dice) return;
	EnemyDicesOnTable[Spot] = Dice;
	Dice->DiceMesh->SetWorldLocation(Spots[Spot], false, nullptr, ETeleportType::None);
	Dice->bIsEnemyChoosen = true;
	OnDicePlacement.ExecuteIfBound(Dice);
}

void ABaseEnemy::ResetDicesPosition()
{
	for (ABaseDice* Dice : EnemyDicesOnHand)
	{
		if (IsValid(Dice))
		{
			Dice->StartLoc();
			Dice->DiceMesh->SetVisibility(true);
			Dice->bIsVisible = true;
		}
	}
	for (ABaseDice*& Slot : EnemyDicesOnTable) Slot = nullptr;
}

void ABaseEnemy::DestroyFangsOnTable()
{
	static const FName Tag(TEXT("Fang"));
	for (ABaseDice*& Dice : EnemyDicesOnTable)
	{
		if (IsValid(Dice) && Dice->ActorHasTag(Tag))
		{
			Dice->Destroy();
			Dice = nullptr;
		}
	}
}

void ABaseEnemy::TableHit()
{
	bWasTableHit = true;
	++TableHitCount;
}