// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameManagers/BrawlManager.h"
#include "Game/GameManagers/WaiterManager.h"
#include "Enemies/BaseEnemy.h"
#include "Player/BasePlayer.h"
#include "Game/GameStateBaseClass.h"
#include "Game/GameManagers/TurnManager.h"

// Sets default values for this component's properties
UBrawlManager::UBrawlManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UBrawlManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Initializing arrays for results and bonuses
	EnemyResults.Init(0, 6);
	PlayerResults.Init(0, 6);
	EnemyBonus.Init(0, 6);
	PlayerBonus.Init(0, 6);
	// Initializing points
	BigPlayerPoints = 0;
	BigEnemyPoints = 0;
}

// Called every frame
void UBrawlManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Initializing references and settings for brawl
void UBrawlManager::Initialize(AGameStateBaseClass *InGameState, ABasePlayer* InPlayer, UTurnManager* InTurnManager)
{
	GameState = InGameState;
	Player = InPlayer;
	TurnManager = InTurnManager;
	CurrentState = ECurrentState::Waiting;
}

// Starting turn when player rolls dices
void UBrawlManager::StartTurn()
{
	// Checking if enemy is new for brawl and setting first player
	if (bIsNewEnemy)
	{
		bIsPlayerFirst = FMath::RandBool();
		TurnManager->WhoseFirst(bIsPlayerFirst);
	}
	// Setting first player for dices placement
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

// Setting sequence for dices placement
void UBrawlManager::DicesPlacementSequence(ABaseDice* PlacedDice)
{
	if (!Enemy) return;
	
	if (CurrentState != ECurrentState::DicePlacement) return;
	
	// Counting placed dices
	ABaseDice* LastDicePlaced = PlacedDice;
	DicePlaced++;
	if (LastDicePlaced->ActorHasTag(FName("BigDice")))
	{
		DicePlaced++;
	}
	
	// Updating dices on table
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
	
	// Swapping order for next dice placement
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
	
	// Checking if all dices are placed on table
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

// Checking brawl results
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
			// Checking if dices are visible and if they have fang tag for result calculation
			if (PlayerDice->bIsVisible && EnemyDice->bIsVisible)
			{
				if (PlayerDice->ActorHasTag(FName("Fang")) ||
					EnemyDice->ActorHasTag(FName("Fang")))
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

	// Counting points for player and enemy
	int PlayerPoints = 0;
	int EnemyPoints = 0;

	for (int i : FinalResults)
	{
		if (i <= -2 ) EnemyPoints++;
		else if (i >= 2) PlayerPoints++;
	}
	if (PlayerPoints > EnemyPoints) BigPlayerPoints++;
	else if (EnemyPoints > PlayerPoints) BigEnemyPoints++;
	
	GameState->TurnCountIncrease();
	bIsNewEnemy = false;
}

// Resetting settings for next brawl
void UBrawlManager::ResetSettings()
{
	if (!Enemy) return;
	Player->Set_bPlayerDiceRolled(false);
	Enemy->bEnemyDiceRolled = false;
	
	// Destroying fangs on table
	Player->DestroyFangsOnTable();
	Enemy->DestroyFangsOnTable();
	DicePlaced = 0;
}

// Resetting dices position
void UBrawlManager::ResetDicesPosition()
{
	if (!Enemy) return;
	CurrentState = ECurrentState::Waiting;
	Player->MoveCamera(ECamPosition::Bottom);
	Player->ResetDicesPosition();
	Enemy->ResetDicesPosition();
}

// Resetting points after brawl
void UBrawlManager::ResetPoints()
{
	if (!Player || !Enemy) return;
	if (BigPlayerPoints != 3 && BigEnemyPoints != 3) return;

	// Player won
	if (BigPlayerPoints >= 3)
	{
		Enemy->GetHit();
		Player->AddGold();
		
		GameState->GetWaiterManager()->RandWaiterServe();
	}
	// Enemy won
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
