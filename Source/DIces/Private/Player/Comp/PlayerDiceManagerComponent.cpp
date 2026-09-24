// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Comp/PlayerDiceManagerComponent.h"
#include "GameFramework/PlayerController.h"
#include "Player/BasePlayer.h"
#include "Dices/BaseDice.h"

UPlayerDiceManagerComponent::UPlayerDiceManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UPlayerDiceManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	DiceSpots.Init(FVector(0, 0, 0), 6);
	DiceSpots[0] = FVector(-5, -25, 97);
	DiceSpots[1] = FVector(-5, -15, 97);
	DiceSpots[2] = FVector(-5, -5, 97);
	DiceSpots[3] = FVector(-5, 5, 97);
	DiceSpots[4] = FVector(-5, 15, 97);
	DiceSpots[5] = FVector(-5, 25, 97);
	
}

void UPlayerDiceManagerComponent::DiceHighlight(bool bValue, ABasePlayer* Player)
{
	if (!IsValid(Player)) return;
	
	for (ABaseDice* Dice : Player->PlayerDices)
	{
		if (IsValid(Dice))
		{
			Dice->bCanHighlight = bValue;
		}
	}
}

void UPlayerDiceManagerComponent::DiceRolling(ECamPosition CurrentCamPos, ABasePlayer* Player)
{
	if (!IsValid(Player)) return;
	if (bPlayerDiceRolled || CurrentCamPos != ECamPosition::Right) return;
	
	for (ABaseDice* Dice :Player->PlayerDicesOnHand)
	{
		if (!IsValid(Dice)) return;
	}
	for (ABaseDice* Dice : Player->PlayerDicesOnHand)
	{
		Dice->PlayerRolling();
		Dice->bIsRolled = true;
	}
	bPlayerDiceRolled = true;
	Player->OnDiceRolled.Broadcast();
}

void UPlayerDiceManagerComponent::ResetDiceForHand(ECamPosition CurrentCamPos, ABasePlayer* Player)
{
	if (!IsValid(Player)) return;
	if (!DiceToSpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("DiceToSpawn is not set"))
		return;
	}
	if (CurrentCamPos == ECamPosition::Left && !bPlayerDiceRolled)
	{
		if (!bAreDicesSpawned)
		{
			for (int32 i = 0; i < 6; i++)
			{
				if (Player->PlayerDices[i] == nullptr)
				{
					Player->PlayerDices[i] = GetWorld()->SpawnActor<ABaseDice>(DiceToSpawn, RandLoc(DiceSpawnLoc, 5), RandRot(DiceSpawnRot, 45));
					if (Player->PlayerDices[i]) Player->PlayerDices[i]->bIsPlayer = true;
				}
			}
			bAreDicesSpawned = true;
		}
		DiceHighlight(true, Player);

		for (ABaseDice* Dice : Player->PlayerDicesOnHand)
		{
			if (IsValid(Dice))
			{
				Dice->bIsChosen = false;
				Dice->bCanHighlight = true;
			}
		}
		bCanChooseDiceForHand = true;
		Player->PlayerDicesOnHand.Init(nullptr, 6);
	}
}

void UPlayerDiceManagerComponent::ResetDicesPosition(ABasePlayer* Player)
{
	if (!IsValid(Player)) return;
	for (int32 i = 0; i < Player->PlayerDicesOnHand.Num(); i++)
	{
		if (IsValid(Player->PlayerDicesOnHand[i]))
		{
			Player->PlayerDicesOnHand[i]->StartLoc();
			Player->PlayerDicesOnHand[i]->DiceMesh->SetVisibility(true);
			Player->PlayerDicesOnHand[i]->bIsVisible = true;
		}
		if (Player->PlayerDicesOnTable.IsValidIndex(i))
		{
			Player->PlayerDicesOnTable[i] = nullptr;
		}
	}
}

void UPlayerDiceManagerComponent::DiceChoose(ECamPosition CurrentCamPos, APlayerController* PlayerController, ABasePlayer* Player)
{
	if (!IsValid(Player)) return;
	if (!PlayerController) return;

	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	ABaseDice* DiceHit = Cast<ABaseDice>(HitResult.GetActor());
	if (!IsValid(DiceHit)) return;
	
	// Choosing player dices on hand
	if (CurrentCamPos == ECamPosition::Left && bCanChooseDiceForHand)
	{
		for (int32 i = 0; i < Player->PlayerDicesOnHand.Num(); i++)
		{
			if (!Player->PlayerDicesOnHand[i] && !DiceHit->bIsChosen)
			{
				Player->PlayerDicesOnHand[i] = DiceHit;
				Player->PlayerDicesOnHand[i]->bIsChosen = true;
				if (i == Player->PlayerDicesOnHand.Num() - 1)
				{
					bCanChooseDiceForHand = false;
				}
				break;
			}
		}
	}
	// Choosing dices for brawl
	else if (CurrentCamPos == ECamPosition::Right)
	{
		if (!bCanChooseDiceForBrawl || !DiceHit->bIsStopped || !DiceHit->bIsRolled
			|| (!Player->PlayerDicesOnHand.Contains(DiceHit) && !DiceHit->ActorHasTag(FName("Fang")))) return;
		
		for (int32 i = 0; i < Player->PlayerDicesOnTable.Num(); i++)
		{
			if (!DiceSpots.IsValidIndex(i)) continue;
			if (!IsValid(Player->PlayerDicesOnTable[i]))
			{
				Player->PlayerDicesOnTable[i] = DiceHit;
				DiceHit->bIsRolled = false;
				Player->PlayerDicesOnTable[i]->DiceMesh->SetWorldLocation(DiceSpots[i], false, nullptr, ETeleportType::None);
				Player->OnDicePlacement.ExecuteIfBound(DiceHit);
				break;
			}
		}
	}
}

FVector UPlayerDiceManagerComponent::RandLoc(FVector Loc, int32 Range)
{
	float X = FMath::RandRange(Loc.X - Range, Loc.X + Range);
	float Y = FMath::RandRange(Loc.Y - Range, Loc.Y + Range);
	float Z = FMath::RandRange(Loc.Z - Range, Loc.Z + Range);
	return FVector(X, Y, Z);
}

FRotator UPlayerDiceManagerComponent::RandRot(FRotator Rot, int32 Range)
{
	float Roll  = FMath::RandRange(Rot.Roll  - Range, Rot.Roll  + Range);
	float Pitch = FMath::RandRange(Rot.Pitch - Range, Rot.Pitch + Range);
	float Yaw   = FMath::RandRange(Rot.Yaw   - Range, Rot.Yaw   + Range);
	return FRotator(Roll, Pitch, Yaw);
}
