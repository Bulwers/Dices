

#pragma once

#include "CoreMinimal.h"
#include "EnemyDecisionComponent.h"
#include "BigEnemyDecisionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UBigEnemyDecisionComponent : public UEnemyDecisionComponent
{
	GENERATED_BODY()
	
protected:
	
	virtual ABaseDice* ChoosingDiceToPutOnTable(
		const TArray<ABaseDice*>& PlayerDicesOnTable,
		const TArray<ABaseDice*>& EnemyDices,
		const int Slot) override;
};
