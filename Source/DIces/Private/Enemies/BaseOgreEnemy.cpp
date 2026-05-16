// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/BaseOgreEnemy.h"

void ABaseOgreEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyDicesOnHand.Init(nullptr, 3);
}

void ABaseOgreEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseOgreEnemy::DeathAction()
{
	for (const int i : { 0, 1, 2 })
	{
		EnemyDicesOnHand[i]->Destroy();
	}
	UE_LOG(LogTemp, Warning, TEXT("Enemy Death Effects Execute"));
	this->Destroy();
}
/*
// Spawning enemy dices
void ABaseOgreEnemy::EnemySpawnDices()
{
	for (const int i : { 0, 1, 2 })
	{
		if (!EnemyDices[i])
		{
			EnemyDices[i] = GetWorld()->SpawnActor<ABaseDice>(DiceToSpawn, RandSpawnLocationForDice(), RandSpawnRotationForDice());
			const FString label(TEXT("EnemyDice"));
			EnemyDices[i]->SetActorLabel(label, false);
		}
	}
}

// Enemy rolling dices
void ABaseOgreEnemy::EnemyDiceRolling()
{
	if (!bEnemyDiceRolled && EnemyDices[0] && EnemyDices[1] && EnemyDices[2])
	{
		for (const int i : { 0, 1, 2 })
		{
			EnemyDices[i]->EnemyRolling();
			EnemyDices[i]->bIsEnemyChoosen = false;
		}

		bEnemyDiceRolled = true;
	}
}

// Enemy choosing dices for brawl
void ABaseOgreEnemy::EnemyChoosingDice()
{
	const TArray<FVector> Spots = {
		FVector(10, -20, 97),
		FVector(10, 0, 97),
		FVector(10, 20, 97)
	};

	for (const int I : { 1, 3, 5 })
	{
		if (bEnemyDiceRolled &&
			!EnemyDicesOnTable[I - 1] &&
			!EnemyDicesOnTable[I] &&
			bEnemyCanChooseDiceForBrawl)
		{
			if (!PlayerDicesOnTable[I - 1] &&
				!PlayerDicesOnTable[I])
			{
				for (const int j : { 0, 1, 2 })
				{
					if (!EnemyDices[Results[j].Y]->bIsEnemyChoosen)
					{
						EnemyDicesOnTable[I - 1] = EnemyDices[Results[j].Y];
						EnemyDicesOnTable[I] = EnemyDices[Results[j].Y];
						break;
					}
				}
			}
			else if (PlayerDicesOnTable[I - 1] &&
					PlayerDicesOnTable[I])
			{
				for (const int K : { 0, 1, 2, 3, 4, 5 })
				{
					for (const int k : { 0, 1, 2, 3, 4, 5 })
					{
						if (PlayerDicesOnTable[I - 1]->Result() == 1 + K &&
							PlayerDicesOnTable[I]->Result() == 1 + k)
						{
							for (const int i : { 0, 1, 2 })
							{
								if (K >= k && K <= 3)
								{
									if (Results[i].X >= 3 + K &&
										!EnemyDices[Results[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I - 1] = EnemyDices[Results[i].Y];
										EnemyDicesOnTable[I] = EnemyDices[Results[i].Y];
										break;
									}
									else if (i == 2)
									{
										break;
									}
								}
								else if (K >= k && K > 3)
								{
									if (Results[i].X >= 1 &&
										!EnemyDices[Results[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I - 1] = EnemyDices[Results[i].Y];
										EnemyDicesOnTable[I] = EnemyDices[Results[i].Y];
										break;
									}
									else if (i == 2)
									{
										break;
									}
								}
								else if (k > K && k <= 3)
								{
									if (Results[i].X >= 3 + k &&
										!EnemyDices[Results[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I - 1] = EnemyDices[Results[i].Y];
										EnemyDicesOnTable[I] = EnemyDices[Results[i].Y];
										break;
									}
									else if (i == 2)
									{
										break;
									}
								}
								else if (k > K && k > 3)
								{
									if (Results[i].X >= 1 &&
										!EnemyDices[Results[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I - 1] = EnemyDices[Results[i].Y];
										EnemyDicesOnTable[I] = EnemyDices[Results[i].Y];
										break;
									}
									else if (i == 2)
									{
										break;
									}
								}
							}
							if (!EnemyDicesOnTable[I - 1] &&
								!EnemyDicesOnTable[I])
							{
								for (const int i : { 0, 1, 2 })
								{
									if (ResultsSorted[i].X >= 1 &&
										!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I - 1] = EnemyDices[ResultsSorted[i].Y];
										EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
										break;
									}
								}
							}
						}
						if (EnemyDicesOnTable[I - 1] &&
							EnemyDicesOnTable[I])
						{
							break;
						}
					}
					if (EnemyDicesOnTable[I - 1] &&
						EnemyDicesOnTable[I])
					{
						break;
					}
				}
			}
			if (EnemyDicesOnTable[I - 1] &&
				EnemyDicesOnTable[I])
			{
				EnemyDicesOnTable[I]->DiceMesh->SetWorldLocation(Spots[(I - 1) / 2], false, nullptr, ETeleportType::None);
				EnemyDicesOnTable[I]->bIsEnemyChoosen = true;
				break;
			}
		}
	}
}*/
