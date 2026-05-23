

#include "Game/GameManagers/BrawlManager.h"
#include "Game/GameManagers/WaiterManager.h"
#include "Enemies/BaseEnemy.h"
#include "Player/BasePlayer.h"
#include "Game/GameStateBaseClass.h"
#include "Game/GameManagers/TurnManager.h"


UBrawlManager::UBrawlManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBrawlManager::BeginPlay()
{
	Super::BeginPlay();
	
	EnemyResults.Init(0, 6);
	PlayerResults.Init(0, 6);
	EnemyBonus.Init(0, 6);
	PlayerBonus.Init(0, 6);
	
	BigPlayerPoints = 0;
	BigEnemyPoints = 0;
}

void UBrawlManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBrawlManager::Initialize(AGameStateBaseClass *InGameState, ABasePlayer* InPlayer, UTurnManager* InTurnManager)
{
	GameState = InGameState;
	Player = InPlayer;
	TurnManager = InTurnManager;
	CurrentState = ECurrentState::Waiting;
}

void UBrawlManager::StartTurn()
{
	if (bIsNewEnemy)
	{
		bIsPlayerFirst = FMath::RandBool();
		TurnManager->WhoseFirst(bIsPlayerFirst);
	}
	if (TurnManager->IsPlayerTurn())
	{
		SetPlacement(true, false, true);
		UE_LOG(LogTemp, Warning, TEXT("Player First"));
	}
	else
	{
		SetPlacement(false, true, false );
		UE_LOG(LogTemp, Warning, TEXT("Enemy First"));
	}
	CurrentState = ECurrentState::DicePlacement;
}

void UBrawlManager::EndTurn()
{
	CheckingResults();
	ResetSettings();
	ResetDicesPosition();
	ResetPoints();
}

void UBrawlManager::DicesPlacementSequence(ABaseDice* PlacedDice)
{
	if (!Enemy) return;
	
	if (CurrentState != ECurrentState::DicePlacement) return;
	
	ABaseDice* LastDicePlaced = PlacedDice;
	DicePlaced++;
	static const FName BigDice(TEXT("BigDice"));
	if (LastDicePlaced->ActorHasTag(BigDice))
	{
		DicePlaced++;
	}
	
	for (int i = 0; i < 6; i++)
	{
		Enemy->PlayerDicesOnTable[i] = Player->PlayerDicesOnTable[i];
		if (Enemy->EnemyDicesOnTable[i])
		{
			EnemyResults[i] = (Enemy->EnemyDicesOnTable[i]->Sum());
		}
		if (Player->PlayerDicesOnTable[i])
		{
			PlayerResults[i] = (Player->PlayerDicesOnTable[i]->Sum());
		}
	}
	
	if (SwapPoints.Contains(DicePlaced))
	{
		TurnManager->SwapOrder();
		UE_LOG(LogTemp, Warning, TEXT("Swap Order"));
		if (TurnManager->IsPlayerTurn())
		{
			SetPlacement(true, false, true);
			UE_LOG(LogTemp, Warning, TEXT("Player turn"));
		}
		else
		{
			SetPlacement(false, true, false);
			UE_LOG(LogTemp, Warning, TEXT("Enemy turn"));
		}
	}
	
	if (Player->PlayerDicesOnTable[5] && Enemy->EnemyDicesOnTable[5])
	{
		SetPlacement(false, false, true);
		bIsPlayerFirst = !bIsPlayerFirst;
		CurrentState = ECurrentState::ScoreResolve;
	}
}

void UBrawlManager::SetPlacement(bool CanPlayerChoose, bool CanEnemyChoose, bool CanPlayerMove)
{
	if (!Player || !Enemy) return;
	Player->Set_bCanChooseDiceForBrawl(CanPlayerChoose);
	Enemy->bEnemyCanChooseDiceForBrawl = CanEnemyChoose;
	Player->Set_bCanMove(CanPlayerMove);
}

void UBrawlManager::CheckingResults()
{
	if (CurrentState != ECurrentState::ScoreResolve) return;
	if (!Player || !Enemy) return;
	
	TArray<int> FinalResults;
	for (const int i : { 0, 1, 2, 3, 4, 5 })
	{
		ABaseDice* PlayerDice = Player->PlayerDicesOnTable[i];
		ABaseDice* EnemyDice = Enemy->EnemyDicesOnTable[i];
		if (PlayerDice && EnemyDice)
		{
			if (PlayerDice->bIsVisible && EnemyDice->bIsVisible)
			{
				static const FName Fang(TEXT("Fang"));
				if (PlayerDice->ActorHasTag(Fang) ||
					EnemyDice->ActorHasTag(Fang))
				{
					FinalResults.Add(0);
				}
				else
				{
					FinalResults.Add((PlayerDice->Sum()) - (EnemyDice->Sum()));
				}
			}
			else
			{
				FinalResults.Add(0);
			}
		}
	}

	int PlayerPoints = 0;
	int EnemyPoints = 0;

	for (int i : FinalResults)
	{
		if (i <= -2) EnemyPoints++;
		else if (i >= 2) PlayerPoints++;
	}
	if (PlayerPoints > EnemyPoints) BigPlayerPoints++;
	else if (EnemyPoints > PlayerPoints) BigEnemyPoints++;
	
	GameState->TurnCountIncrease();
	bIsNewEnemy = false;
}

void UBrawlManager::ResetSettings()
{
	if (!Enemy) return;
	Player->Set_bPlayerDiceRolled(false);
	Enemy->bEnemyDiceRolled = false;
	
	Player->DestroyFangsOnTable();
	Enemy->DestroyFangsOnTable();
	DicePlaced = 0;
}

void UBrawlManager::ResetDicesPosition()
{
	if (!Enemy) return;
	CurrentState = ECurrentState::Waiting;
	Player->MoveCamera(ECamPosition::Bottom);
	
	Player->ResetDicesPosition();
	for (int& Result : PlayerResults) Result = 0;
	Enemy->ResetDicesPosition();
	for (int& Result : EnemyResults) Result = 0;
}

void UBrawlManager::ResetPoints()
{
	if (!Player || !Enemy) return;
	if (BigPlayerPoints != 3 && BigEnemyPoints != 3) return;

	if (BigPlayerPoints >= 3)
	{
		Enemy->GetHit();
		Player->AddGold();
		
		GameState->GetWaiterManager()->RandWaiterServe();
	}
	else if (BigEnemyPoints >= 3)
	{	
		Player->GetHit();
		Player->FangSpawn();
		if (Player->GetHealth() > 0)
		{
			GameState->GetWaiterManager()->RandWaiterServe();
		}
	}
	BigPlayerPoints = 0;
	BigEnemyPoints = 0;
}
