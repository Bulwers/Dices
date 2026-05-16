

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
	
	// Finds slot index to place dice on table // Returns -1 if there is no slot to place dice
	UFUNCTION(BlueprintCallable)
	virtual int FindSlotToPlaceDice(const TArray<ABaseDice*>& PlayerDicesOnTable, const TArray<ABaseDice*>& EnemyDicesOnTable);
	UFUNCTION(BlueprintCallable)
	virtual ABaseDice* ChoosingDiceToPutOnTable(const TArray<ABaseDice*>& PlayerDicesOnTable, const TArray<ABaseDice*>& EnemyDicesOnTable, const TArray<ABaseDice*>& EnemyDices);
	
protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	EDicePlacementDecision EEnemyPlacementDecision;
	
	UPROPERTY()
	class UEnemyStrategy* Strategy;
	UPROPERTY(EditAnywhere)
	FName StrategyName;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
