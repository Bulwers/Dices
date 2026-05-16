// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DiceBuffArea.h"
#include "Player/BasePlayer.h"
#include "Player/Conditions/BaseCondition.h"
#include "Kismet/GameplayStatics.h"

ADiceBuffArea::ADiceBuffArea()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerArea = CreateDefaultSubobject<UBuffTriggerAreaComponent>(TEXT("TriggerArea"));
	RootComponent = TriggerArea;
}

void ADiceBuffArea::BeginPlay()
{
	Super::BeginPlay();

	OnClicked.AddDynamic(this, &ADiceBuffArea::DiceBuff);

	Player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void ADiceBuffArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADiceBuffArea::DiceBuff(AActor* ActorClicked, FKey InKey)
{
	if (Player->bPlusOneBuff)
	{
		TriggerArea->PlayerDice->Bonus = 1;

		for (int i : { 0, 1, 2, 3, 4, 5 })
		{
			if (Player->DrinkConditions[i] && Player->DrinkConditions[i]->ComponentTags.Contains(FName("PlusOne")))
			{
				Player->DrinkConditions[i]->DrinkEffect();
			}
		}
	}
	if (Player->bPlusTwoBuff)
	{
		TriggerArea->PlayerDice->Bonus = 2;

		for (int i : { 0, 1, 2, 3, 4, 5 })
		{
			if (Player->DrinkConditions[i] && Player->DrinkConditions[i]->ComponentTags.Contains(FName("PlusTwo")))
			{
				Player->DrinkConditions[i]->DrinkEffect();
			}
		}
	}
}