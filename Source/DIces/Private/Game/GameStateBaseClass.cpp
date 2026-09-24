

#include "Game/GameStateBaseClass.h"
#include "Player/BasePlayer.h"
#include "Enemies/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Game/GameManagers/TurnManager.h"
#include "Game/GameManagers/BrawlManager.h"
#include "Game/GameManagers/WaiterManager.h"

AGameStateBaseClass::AGameStateBaseClass()
{
	PrimaryActorTick.bCanEverTick = true;

	TurnManager = CreateDefaultSubobject<UTurnManager>(TEXT("TurnManager"));
	BrawlManager = CreateDefaultSubobject<UBrawlManager>(TEXT("BrawlManager"));
	WaiterManager = CreateDefaultSubobject<UWaiterManager>(TEXT("WaiterManager"));
}

void AGameStateBaseClass::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player not found!"));
		return;
	}
	Player->OnDiceRolled.AddUObject(BrawlManager, &UBrawlManager::StartTurn);
	Player->OnDicePlacement.BindUObject(BrawlManager, &UBrawlManager::DicesPlacementSequence);
	WaiterManager->WaiterCall.BindUObject(BrawlManager, &UBrawlManager::SetWaiterState);
	TurnManager->SetWaitingTurn();
	BrawlManager->Initialize(this, Player, TurnManager);
	
	bCameraBlock = false;
	Enemy = nullptr;
}

void AGameStateBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TO DO
	// CHANGE TO EVENT-DRIVEN
	if (!Enemy && GetBrawlManager()->GetCurrentState() != ECurrentState::WaiterServe)
	{
		const int32 EnemyIndex = RandEnemy();
		if (EnemyIndex == INDEX_NONE || !EnemiesToSpawn.IsValidIndex(EnemyIndex) || !EnemiesToSpawn[EnemyIndex])
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot spawn enemy"));
			return;
		}
		Enemy = GetWorld()->SpawnActor<ABaseEnemy>(EnemiesToSpawn[EnemyIndex], EnemySpawnLoc, EnemySpawnRot);
		if (Enemy)
		{
			BrawlManager->SetNewEnemy();
			BrawlManager->InitializeEnemy(Enemy);
			Enemy->EnemyDiedDelegate.BindUObject(this, &AGameStateBaseClass::EnemyReset);
			Enemy->OnDicePlacement.BindUObject(BrawlManager, &UBrawlManager::DicesPlacementSequence);
		}
	}
	// TO DO
	// CHANGE TO EVENT-DRIVEN
	PlayerCameraBlock();
}

int AGameStateBaseClass::RandEnemy()
{
	if (EnemiesToSpawn.IsEmpty()) return INDEX_NONE;

	return FMath::RandRange(0, EnemiesToSpawn.Num() - 1);
}

void AGameStateBaseClass::EnemyReset()
{
	Enemy = nullptr;
	EnemiesCount++;
	WaiterManager->WaiterServe();
	UE_LOG(LogTemp, Warning, TEXT("Waiter Call"));
}

void AGameStateBaseClass::PlayerCameraBlock()
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player not found!"));
		return;
	}
	
	if (BrawlManager->GetCurrentState() == ECurrentState::WaiterServe)
	{
		Player->Set_bCanMove(false);
	}
	else if (Enemy && !bCameraBlock)
	{
		if (Enemy->bIsEnemyOnSpot)
		{
			Player->Set_bCanMove(true);
			bCameraBlock = true;
		}
		else
		{
			Player->Set_bCanMove(false);
			bCameraBlock = false;
		}
	}
}