

#include "Drinks/PlusOneDrink.h"
#include "Player/Conditions/PlusOneCondition.h"

void APlusOneDrink::BeginPlay()
{
	Super::BeginPlay();
}

void APlusOneDrink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlusOneDrink::Drink()
{
	for (UBaseCondition* Condition : Player->DrinkConditions)
	{
		if (Condition == nullptr)
		{
			Condition = NewObject<UPlusOneCondition>(Player);
			Condition->RegisterComponent();
			break;
		}
	}
	Destroy();
}