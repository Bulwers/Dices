

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyDecisionComponent.generated.h"

class ABaseDice;

UENUM(BlueprintType)
enum class EDicePlacementDecision : uint8
{
	BlindPlacement		UMETA(DisplayName = "Blind Placement"),
	KnowingPlacement	UMETA(DisplayName = "Knowing Placement")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UEnemyDecisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UEnemyDecisionComponent();
	
	TPair<ABaseDice*, int> GetDiceToPlace(
		const TArray<ABaseDice*>& PlayerDicesOnTable,
		const TArray<ABaseDice*>& EnemyDicesOnTable,
		const TArray<ABaseDice*>& EnemyDicesOnHand);

	UFUNCTION()
	void SetStrategy(const FName StrategyName);
	
	
protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	EDicePlacementDecision EEnemyPlacementDecision;
	
	// Finds slot index to place dice on table // Returns -1 if there is no slot to place dice
	virtual int FindSlotToPlaceDice(
		const TArray<ABaseDice*>& PlayerDicesOnTable, 
		const TArray<ABaseDice*>& EnemyDicesOnTable);
	
	virtual ABaseDice* ChoosingDiceToPutOnTable(
		const TArray<ABaseDice*>& PlayerDicesOnTable,
		const TArray<ABaseDice*>& EnemyDices,
		const int Slot);
	
	UPROPERTY()
	class UEnemyStrategy* Strategy;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
