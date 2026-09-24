

#include "Enemies/Comp/EnemyDiceComponent.h"
#include "Dices/BaseDice.h"
#include "Enemies/BaseEnemy.h"

UEnemyDiceComponent::UEnemyDiceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyDiceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEnemyDiceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

FVector UEnemyDiceComponent::RandSpawnLocationForDice()
{
	const float Loc_X = FMath::RandRange(90, 100);
	const float Loc_Y = FMath::RandRange(60, 70);
	const float Loc_Z = FMath::RandRange(110, 120);
	return FVector(Loc_X, Loc_Y, Loc_Z);
}

FRotator UEnemyDiceComponent::RandSpawnRotationForDice()
{
	const float Rot_X = FMath::RandRange(0, 90);
	const float Rot_Y = FMath::RandRange(0, 90);
	const float Rot_Z = FMath::RandRange(0, 90);
	return FRotator(Rot_X, Rot_Y, Rot_Z);
}

void UEnemyDiceComponent::SpawnDices(TArray<TObjectPtr<ABaseDice>>& EnemyDices, TArray<TSubclassOf<ABaseDice>> DicesToSpawn, ABaseEnemy* Owner)
{
	for (int i = 0; i < EnemyDices.Num(); i++)
	{
		if (!EnemyDices[i] && DicesToSpawn.IsValidIndex(i))
		{
			EnemyDices[i] = GetWorld()->SpawnActor<ABaseDice>(DicesToSpawn[i], RandSpawnLocationForDice(), RandSpawnRotationForDice());
			if (!EnemyDices[i]) continue;
			EnemyDices[i]->SetActorLabel(TEXT("EnemyDice"), false);
			EnemyDices[i]->OnDiceStopped.BindLambda([this, Owner](){OnSingleDiceStopped(Owner);});
		}
	}
}

void UEnemyDiceComponent::OnSingleDiceStopped(ABaseEnemy* Owner)
{
	Owner->bAreAllDicesStopped = AreAllDicesStopped(Owner);
}

bool UEnemyDiceComponent::AreAllDicesStopped(ABaseEnemy* Owner)
{
	for (ABaseDice* Dice : Owner->EnemyDicesOnHand)
	{
		if (!Dice->bIsStopped)
		{
			return false;
		}
	}
	return true;
}