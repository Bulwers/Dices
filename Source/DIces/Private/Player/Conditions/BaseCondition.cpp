// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Conditions/BaseCondition.h"

// Sets default values for this component's properties
UBaseCondition::UBaseCondition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UBaseCondition::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<AGameStateBaseClass>(GetWorld()->GetGameState());
	StartTurnCount = GameState->GetTurnCount();
	NewTurnCount = GameState->GetTurnCount();

	Player = Cast<ABasePlayer>(GetOwner());
	bCanBuff = false;
}

// Called every frame
void UBaseCondition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ActualTurnCount = GameState->GetTurnCount();

}

void UBaseCondition::DrinkEffect()
{

}