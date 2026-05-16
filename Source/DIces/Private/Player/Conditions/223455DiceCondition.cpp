// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Conditions/223455DiceCondition.h"

void U223455DiceCondition::BeginPlay()
{
	Super::BeginPlay();

	TempDiceToSpawn = LoadClass<ABaseDice>(nullptr, TEXT("/Game/Dices/BP_223455Dice.BP_223455Dice_C"));

	PlayerDices.Init(nullptr, 6);
	TempDices.Init(nullptr, 6);

	DrinkEffect();
}

void U223455DiceCondition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Lifetime
	if (ActualTurnCount - StartTurnCount >= 2)
	{
		for (int i = 0; i < 6; i++)
		{
			if (Player->PlayerDicesOnHand[i])
			{
				Player->PlayerDicesOnHand[i] = PlayerDices[i];

				Player->PlayerDicesOnHand[i]->SetActorHiddenInGame(false);
				Player->PlayerDicesOnHand[i]->DiceMesh->SetSimulatePhysics(true);
				Player->PlayerDicesOnHand[i]->SetActorEnableCollision(true);

				TempDices[i]->Destroy();
			}
		}
		DestroyComponent();
	}
}

void U223455DiceCondition::DrinkEffect()
{
	for (int i = 0; i < 6; i++)
	{
		if (Player->PlayerDicesOnHand[i])
		{
			PlayerDices[i] = Player->PlayerDicesOnHand[i];

			Player->PlayerDicesOnHand[i]->SetActorHiddenInGame(true);
			Player->PlayerDicesOnHand[i]->DiceMesh->SetSimulatePhysics(false);
			Player->PlayerDicesOnHand[i]->SetActorEnableCollision(false);

			TempDices[i] = GetWorld()->SpawnActor<ABaseDice>(TempDiceToSpawn, Player->PlayerDicesOnHand[i]->GetActorLocation(), Player->PlayerDicesOnHand[i]->GetActorRotation());

			Player->PlayerDicesOnHand[i] = TempDices[i];
			Player->PlayerDicesOnHand[i]->bIsChoosen = true;
			Player->PlayerDicesOnHand[i]->bIsPlayer = true;
		}
	}
}
