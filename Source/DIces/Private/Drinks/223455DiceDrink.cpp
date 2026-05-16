

#include "Drinks/223455DiceDrink.h"
#include "Player/Conditions/223455DiceCondition.h"

void A223455DiceDrink::BeginPlay()
{
	Super::BeginPlay();
}

void A223455DiceDrink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void A223455DiceDrink::Drink()
{
	for (UBaseCondition* Condition : Player->DrinkConditions)
	{
		if (Condition == nullptr)
		{
			Condition = NewObject<U223455DiceCondition>(Player);
			Condition->RegisterComponent();
			break;
		}
	}
	Destroy();
}
