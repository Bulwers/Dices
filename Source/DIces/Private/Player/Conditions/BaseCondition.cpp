

#include "Player/Conditions/BaseCondition.h"
#include "Player/BasePlayer.h"
#include "Game/GameStateBaseClass.h"

UBaseCondition::UBaseCondition()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBaseCondition::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<AGameStateBaseClass>(GetWorld()->GetGameState());
	if (!IsValid(GameState))
	{
		UE_LOG(LogTemp, Error, TEXT("GameState not found / UBaseCondition"));
	}
	StartTurnCount = GameState->GetTurnCount();
	NewTurnCount = GameState->GetTurnCount();

	Player = Cast<ABasePlayer>(GetOwner());
	if (!IsValid(Player))
	{
		UE_LOG(LogTemp, Error, TEXT("Player not found / UBasePlayer"));
	}
	bCanBuff = false;
}

void UBaseCondition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(GameState)) return;
	ActualTurnCount = GameState->GetTurnCount();
}

void UBaseCondition::DrinkEffect()
{
}