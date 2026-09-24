

#include "Dices/FangDice.h"

AFangDice::AFangDice()
{
	Tags.Add(FName("Fang"));
}

void AFangDice::BeginPlay()
{
	Super::BeginPlay();
	
	bIsRolled = true;
	
	bIsPlayer = true;
	bIsChosen = true;
	bIsEnemyChosen = false;
	bCanHighlight = false;
	bIsStopped = true;
	bIsVisible = true;
}

int AFangDice::Result()
{
	return 6;
}
