#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyDiceComponent.generated.h"

class ABaseDice;
class ABaseEnemy;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UEnemyDiceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UEnemyDiceComponent();
	
	UFUNCTION()
	void SpawnDices(TArray<ABaseDice*> &EnemyDices, TArray<TSubclassOf<ABaseDice>> DicesToSpawn, ABaseEnemy* Owner);
	
protected:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	FVector RandSpawnLocationForDice();
	UFUNCTION()
	FRotator RandSpawnRotationForDice();

	UFUNCTION()
	void OnSingleDiceStopped(ABaseEnemy* Owner);
	UFUNCTION()
	bool AreAllDicesStopped(ABaseEnemy* Owner);

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
