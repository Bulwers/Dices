

#include "Drinks/LuckyDrink.h"
#include "Player/Conditions/LuckyDrinkCondition.h"

void ALuckyDrink::BeginPlay()
{
	Super::BeginPlay();
}

void ALuckyDrink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALuckyDrink::Drink()
{
	for (UBaseCondition* Condition : Player->DrinkConditions)
	{
		if (Condition == nullptr)
		{
			Condition = NewObject<ULuckyDrinkCondition>(Player);
			Condition->RegisterComponent();
			break;
		}
	}
	Destroy();
}