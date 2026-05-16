// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemies/Bosses/Chef.h"
#include "Misc/Items/Chopper.h"

void AChef::BeginPlay()
{
	Super::BeginPlay();
}

void AChef::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChef::DiceCheckForHit()
{
	UE_LOG(LogTemp, Warning, TEXT("Chef Dice Check"));
	for (const int i : { 1, 5 })
	{
		if (PlayerDicesOnTable[i] && EnemyDicesOnTable[i])
		{
			// Hitting with chopper if one or 2 pairs of dices is loosing
			if ((((PlayerDicesOnTable[i]->Result() - EnemyDicesOnTable[i]->Result()) >= 2) &&
				((PlayerDicesOnTable[i-1]->Result() - EnemyDicesOnTable[i-1]->Result()) >= 0)) ||
				(((PlayerDicesOnTable[i]->Result() - EnemyDicesOnTable[i]->Result()) >= 0) &&
				((PlayerDicesOnTable[i-1]->Result() - EnemyDicesOnTable[i-1]->Result()) >= 2)))
			{
				Chopper->ChopperHit(i);
				Chopper->ChopperHit(i-1);
				UE_LOG(LogTemp, Warning, TEXT("Chopper Hit"));
				break;
			}
		}
	}
}

void AChef ::ChopperSpawn()
{
	Chopper = GetWorld()->SpawnActor<AChopper>(ChopperToSpawn, ChopperLoc, ChopperRot);
}
/*
void AChef::EnemyChoosingDice()
{
	TArray<FVector> Spots;
	Spots.Add(FVector(5, -25, 97));
	Spots.Add(FVector(5, -15, 97));
	Spots.Add(FVector(5, -5, 97));
	Spots.Add(FVector(5, 5, 97));
	Spots.Add(FVector(5, 15, 97));
	Spots.Add(FVector(5, 25, 97));

	for (const int I : { 0, 1, 2, 3, 4, 5 })
	{
		if (bEnemyDiceRolled &&
			!EnemyDicesOnTable[I] &&
			bEnemyCanChooseDiceForBrawl)
		{
			if (!PlayerDicesOnTable[I])
			{
				if (I == 2 || I == 3)
				{
					for (const int i : { 0, 1, 2, 3, 4, 5 })
					{
						if ((ResultsSorted[i].X == 6 || ResultsSorted[i].X == 5) &&
							!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
						{
							EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
							EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
							break;
						}
						else if (i == 5)
						{
							for (const int j : { 0, 1, 2, 3, 4, 5 })
							{
								if (!EnemyDices[Results[j].Y]->bIsEnemyChoosen)
								{
									EnemyDicesOnTable[I] = EnemyDices[Results[j].Y];
									EnemyDicesOnTableIndex[I] = Results[j].Y;
									break;
								}
							}
						}
					}
				}
				else
				{
					for (const int j : { 0, 1, 2, 3, 4, 5 })
					{
						if (!EnemyDices[Results[j].Y]->bIsEnemyChoosen)
						{
							EnemyDicesOnTable[I] = EnemyDices[Results[j].Y];
							EnemyDicesOnTableIndex[I] = Results[j].Y;
							break;
						}
					}
				}

			}
			else if (PlayerDicesOnTable[I])
			{
				if (I == 2 || I == 3)
				{

					for (const int k : { 0, 1, 2, 3, 4, 5 })
					{
						if ((ResultsSorted[k].X == 6 || ResultsSorted[k].X == 5) &&
							!EnemyDices[ResultsSorted[k].Y]->bIsEnemyChoosen)
						{
							EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[k].Y];
							EnemyDicesOnTableIndex[I] = ResultsSorted[k].Y;
							break;
						}
						else if (k == 5)
						{
							if (PlayerDicesOnTable[I]->Result() == 1)
							{
								for (const int i : { 0, 1, 2, 3, 4, 5 })
								{
									if ((ResultsSorted[i].X == 3 || ResultsSorted[i].X == 4) &&
										!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
										EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
										break;
									}
									else if (i == 5)
									{
										break;
									}
								}
								if (!EnemyDicesOnTable[I])
								{
									for (const int i : { 0, 1, 2, 3, 4, 5 })
									{
										if (ResultsSorted[i].X >= 1 &&
											!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
										{
											EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
											EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
											break;
										}
									}
								}
							}
							else if (PlayerDicesOnTable[I]->Result() == 2)
							{
								for (const int i : { 0, 1, 2, 3, 4, 5 })
								{
									if (ResultsSorted[i].X == 4 &&
										!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
										EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
										break;
									}
									else if (i == 5)
									{
										break;
									}
								}
								if (!EnemyDicesOnTable[I])
								{
									for (const int i : { 0, 1, 2, 3, 4, 5 })
									{
										if (ResultsSorted[i].X >= 1 &&
											!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
										{
											EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
											EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
											break;
										}
									}
								}
							}
							else if (PlayerDicesOnTable[I]->Result() == 3)
							{
								for (const int i : { 0, 1, 2, 3, 4, 5 })
								{
									if (ResultsSorted[i].X == 5 &&
										!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
										EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
										break;
									}
									else if (i == 5)
									{
										break;
									}
								}
								if (!EnemyDicesOnTable[I])
								{
									for (const int i : { 0, 1, 2, 3, 4, 5 })
									{
										if (ResultsSorted[i].X >= 2 &&
											!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
										{
											EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
											EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
											break;
										}
										else if (i == 5)
										{
											break;
										}
									}
								}
								if (!EnemyDicesOnTable[I])
								{
									for (const int i : { 0, 1, 2, 3, 4, 5 })
									{
										if (ResultsSorted[i].X == 1 &&
											!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
										{
											EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
											EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
											break;
										}
									}
								}
							}
							else if (PlayerDicesOnTable[I]->Result() == 4)
							{
								for (const int i : { 0, 1, 2, 3, 4, 5 })
								{
									if (ResultsSorted[i].X == 6 &&
										!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
										EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
										break;
									}
									else if (i == 5)
									{
										break;
									}
								}
								if (!EnemyDicesOnTable[I])
								{
									for (const int i : { 0, 1, 2, 3, 4, 5 })
									{
										if (ResultsSorted[i].X >= 3 &&
											!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
										{
											EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
											EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
											break;
										}
										else if (i == 5)
										{
											break;
										}
									}
								}
								if (!EnemyDicesOnTable[I])
								{
									for (const int i : { 0, 1, 2, 3, 4, 5 })
									{
										if (ResultsSorted[i].X >= 1 &&
											!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
										{
											EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
											EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
											break;
										}
									}
								}
							}
							else if (PlayerDicesOnTable[I]->Result() == 5)
							{
								for (const int i : { 0, 1, 2, 3, 4, 5 })
								{
									if (ResultsSorted[i].X >= 4 &&
										!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
										EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
										break;
									}
									else if (i == 5)
									{
										break;
									}
								}
								if (!EnemyDicesOnTable[I])
								{
									for (const int i : { 0, 1, 2, 3, 4, 5 })
									{
										if (ResultsSorted[i].X >= 1 &&
											!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
										{
											EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
											EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
											break;
										}
									}
								}
							}
							else if (PlayerDicesOnTable[I]->Result() == 6)
							{
								for (const int i : { 0, 1, 2, 3, 4, 5 })
								{
									if (ResultsSorted[i].X >= 5 &&
										!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
									{
										EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
										EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
										break;
									}
									else if (i == 5)
									{
										break;
									}
								}
								if (!EnemyDicesOnTable[I])
								{
									for (const int i : { 0, 1, 2, 3, 4, 5 })
									{
										if (ResultsSorted[i].X >= 1 &&
											!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
										{
											EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
											EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
											break;
										}
									}
								}
							}
						}
					}
				}
				else
				{
					if (PlayerDicesOnTable[I]->Result() == 1)
					{
						for (const int i : { 0, 1, 2, 3, 4, 5 })
						{
							if ((ResultsSorted[i].X == 3 || ResultsSorted[i].X == 4) &&
								!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
							{
								EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
								EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
								break;
							}
							else if (i == 5)
							{
								break;
							}
						}
						if (!EnemyDicesOnTable[I])
						{
							for (const int i : { 0, 1, 2, 3, 4, 5 })
							{
								if (ResultsSorted[i].X >= 1 &&
									!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
								{
									EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
									EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
									break;
								}
							}
						}
					}
					else if (PlayerDicesOnTable[I]->Result() == 2)
					{
						for (const int i : { 0, 1, 2, 3, 4, 5 })
						{
							if (ResultsSorted[i].X == 4 &&
								!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
							{
								EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
								EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
								break;
							}
							else if (i == 5)
							{
								break;
							}
						}
						if (!EnemyDicesOnTable[I])
						{
							for (const int i : { 0, 1, 2, 3, 4, 5 })
							{
								if (ResultsSorted[i].X >= 1 &&
									!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
								{
									EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
									EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
									break;
								}
							}
						}
					}
					else if (PlayerDicesOnTable[I]->Result() == 3)
					{
						for (const int i : { 0, 1, 2, 3, 4, 5 })
						{
							if (ResultsSorted[i].X == 5 &&
								!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
							{
								EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
								EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
								break;
							}
							else if (i == 5)
							{
								break;
							}
						}
						if (!EnemyDicesOnTable[I])
						{
							for (const int i : { 0, 1, 2, 3, 4, 5 })
							{
								if (ResultsSorted[i].X >= 2 &&
									!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
								{
									EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
									EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
									break;
								}
								else if (i == 5)
								{
									break;
								}
							}
						}
						if (!EnemyDicesOnTable[I])
						{
							for (const int i : { 0, 1, 2, 3, 4, 5 })
							{
								if (ResultsSorted[i].X == 1 &&
									!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
								{
									EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
									EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
									break;
								}
							}
						}
					}
					else if (PlayerDicesOnTable[I]->Result() == 4)
					{
						for (const int i : { 0, 1, 2, 3, 4, 5 })
						{
							if (ResultsSorted[i].X == 6 &&
								!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
							{
								EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
								EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
								break;
							}
							else if (i == 5)
							{
								break;
							}
						}
						if (!EnemyDicesOnTable[I])
						{
							for (const int i : { 0, 1, 2, 3, 4, 5 })
							{
								if (ResultsSorted[i].X >= 3 &&
									!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
								{
									EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
									EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
									break;
								}
								else if (i == 5)
								{
									break;
								}
							}
						}
						if (!EnemyDicesOnTable[I])
						{
							for (const int i : { 0, 1, 2, 3, 4, 5 })
							{
								if (ResultsSorted[i].X >= 1 &&
									!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
								{
									EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
									EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
									break;
								}
							}
						}
					}
					else if (PlayerDicesOnTable[I]->Result() == 5)
					{
						for (const int i : { 0, 1, 2, 3, 4, 5 })
						{
							if (ResultsSorted[i].X >= 4 &&
								!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
							{
								EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
								EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
								break;
							}
							else if (i == 5)
							{
								break;
							}
						}
						if (!EnemyDicesOnTable[I])
						{
							for (const int i : { 0, 1, 2, 3, 4, 5 })
							{
								if (ResultsSorted[i].X >= 1 &&
									!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
								{
									EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
									EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
									break;
								}
							}
						}
					}
					else if (PlayerDicesOnTable[I]->Result() == 6)
					{
						for (const int i : { 0, 1, 2, 3, 4, 5 })
						{
							if (ResultsSorted[i].X >= 5 &&
								!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
							{
								EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
								EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
								break;
							}
							else if (i == 5)
							{
								break;
							}
						}
						if (!EnemyDicesOnTable[I])
						{
							for (const int i : { 0, 1, 2, 3, 4, 5 })
							{
								if (ResultsSorted[i].X >= 1 &&
									!EnemyDices[ResultsSorted[i].Y]->bIsEnemyChoosen)
								{
									EnemyDicesOnTable[I] = EnemyDices[ResultsSorted[i].Y];
									EnemyDicesOnTableIndex[I] = ResultsSorted[i].Y;
									break;
								}
							}
						}
					}
				}
			}
			if (EnemyDicesOnTable[I])
			{
				EnemyDicesOnTable[I]->DiceMesh->SetWorldLocation(Spots[I], false, nullptr, ETeleportType::None);
				EnemyDicesOnTable[I]->bIsEnemyChoosen = true;
				break;
			}
		}
	}
}*/

