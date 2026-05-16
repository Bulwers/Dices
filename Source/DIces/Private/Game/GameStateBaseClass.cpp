

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

	if (!Enemy && GetBrawlManager()->GetCurrentState() != ECurrentState::WaiterServe)
	{
		//FVector SpawnLoc (170, 200, 88);
		//FRotator SpawnRot (0, 0, 0);
		Enemy = GetWorld()->SpawnActor<ABaseEnemy>(RandEnemyToSpawn[RandEnemy()], EnemySpawnLoc, EnemySpawnRot);
		BrawlManager->SetNewEnemy();
		BrawlManager->InitializeEnemy(Enemy);
		Enemy->EnemyDiedDelegate.BindUObject(this, &AGameStateBaseClass::EnemyReset);
		Enemy->OnDicePlacement.BindUObject(BrawlManager, &UBrawlManager::DicesPlacementSequence);
	}
	PlayerCameraBlock();
}

int AGameStateBaseClass::RandEnemy()
{
	int RandEnemyIndex = FMath::RandRange(0, 3);

	return RandEnemyIndex;
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