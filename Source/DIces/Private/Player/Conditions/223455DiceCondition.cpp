

#include "Player/Conditions/223455DiceCondition.h"
#include "Player/BasePlayer.h"
#include "Dices/BaseDice.h"

void U223455DiceCondition::BeginPlay()
{
	Super::BeginPlay();

	TempDiceToSpawn = LoadClass<ABaseDice>(nullptr, TEXT("/Game/Dices/BP_223455Dice.BP_223455Dice_C"));

	if (!TempDiceToSpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Dice class / 223455DiceCondition"));
		return;
	}
	PlayerDices.Init(nullptr, 6);
	TempDices.Init(nullptr, 6);

	DrinkEffect();
}

void U223455DiceCondition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActualTurnCount - StartTurnCount >= TurnLifetime)
	{
		for (int32 i = 0 ; i < Player->PlayerDicesOnHand.Num(); i++)
		{
			if (!IsValid(PlayerDices[i])) continue;
			if (Player->PlayerDicesOnHand[i])
			{
				Player->PlayerDicesOnHand[i] = PlayerDices[i];

				Player->PlayerDicesOnHand[i]->SetActorHiddenInGame(false);
				Player->PlayerDicesOnHand[i]->DiceMesh->SetSimulatePhysics(true);
				Player->PlayerDicesOnHand[i]->SetActorEnableCollision(true);
				
				if (IsValid(TempDices[i]))
				{
					TempDices[i]->Destroy();
				}
			}
		}
		DestroyComponent();
	}
}

void U223455DiceCondition::DrinkEffect()
{
	for (int32 i = 0 ; i < Player->PlayerDicesOnHand.Num(); i++)
	{
		if (Player->PlayerDicesOnHand[i])
		{
			PlayerDices[i] = Player->PlayerDicesOnHand[i];

			Player->PlayerDicesOnHand[i]->SetActorHiddenInGame(true);
			Player->PlayerDicesOnHand[i]->DiceMesh->SetSimulatePhysics(false);
			Player->PlayerDicesOnHand[i]->SetActorEnableCollision(false);

			TempDices[i] = GetWorld()->SpawnActor<ABaseDice>(TempDiceToSpawn, Player->PlayerDicesOnHand[i]->GetActorLocation(), Player->PlayerDicesOnHand[i]->GetActorRotation());
			if (!IsValid(TempDices[i]))
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to spawn TempDice / 223455DiceCondition"));
			}
			
			Player->PlayerDicesOnHand[i] = TempDices[i];
			Player->PlayerDicesOnHand[i]->bIsChosen = true;
			Player->PlayerDicesOnHand[i]->bIsPlayer = true;
		}
	}
}
