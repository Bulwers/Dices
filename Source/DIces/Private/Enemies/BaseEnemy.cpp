

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
	EnemyDiceComp = CreateDefaultSubobject<UEnemyDiceComponent>(TEXT("EnemyDiceComp"));
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player) Player->OnDiceRolled.AddUObject(this, &ABaseEnemy::EnemyDiceRolling);
	
	EnemyHealthComp->OnDeathEffects.BindUObject(this, &ABaseEnemy::DeathAction);
	
	EnemyDecisionComp = NewObject<UEnemyDecisionComponent>(this, DecisionComponentToSpawn, TEXT("EnemyDecisionComp"));
	EnemyDecisionComp->RegisterComponent();
	EnemyDecisionComp->SetStrategy(StrategyName);
	
	DialogueManager = Cast<ADialogueManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ADialogueManager::StaticClass()));
	if (!DialogueManager) UE_LOG(LogTemp, Warning, TEXT("DialogueManager not found"));
	
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
	TPair<ABaseDice*, int> const DiceAndSlot = EnemyDecisionComp->GetDiceToPlace(PlayerDicesOnTable, EnemyDicesOnTable, EnemyDicesOnHand);
	const int Spot = DiceAndSlot.Value;
	ABaseDice* Dice = DiceAndSlot.Key;
	if (!Dice) return;
	EnemyDicesOnTable[Spot] = Dice;
	static const FName BigDice(TEXT("BigDice"));
	if (Dice->ActorHasTag(BigDice))
	{
		EnemyDicesOnTable[Spot + 1] = Dice;
		Dice->DiceMesh->SetWorldLocation(DicesSpots[Spot/2], false, nullptr, ETeleportType::None);
	}
	else Dice->DiceMesh->SetWorldLocation(DicesSpots[Spot], false, nullptr, ETeleportType::None);
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
	static const FName Fang(TEXT("Fang"));
	for (ABaseDice*& Dice : EnemyDicesOnTable)
	{
		if (IsValid(Dice) && Dice->ActorHasTag(Fang))
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