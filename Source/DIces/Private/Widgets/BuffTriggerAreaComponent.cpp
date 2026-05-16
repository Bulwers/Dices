// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuffTriggerAreaComponent.h"
#include "Dices/BaseDice.h"

UBuffTriggerAreaComponent::UBuffTriggerAreaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuffTriggerAreaComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBuffTriggerAreaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> Dices;
	GetOverlappingActors(Dices);
	for (AActor* Dice : Dices)
	{
		if (Dice->ActorHasTag("Dice"))
		{
			PlayerDice = Cast<ABaseDice>(Dice);
		}
	}
}
