
#pragma once

#include "CoreMinimal.h"
#include "Dices/BaseDice.h"
#include "GameFramework/Pawn.h"
#include "BaseEnemy.generated.h"

DECLARE_DELEGATE(FEnemyDied);
DECLARE_DELEGATE_OneParam(FDicePlacement, ABaseDice*);

UCLASS()
class DICES_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	
	ABaseEnemy();

	FEnemyDied EnemyDiedDelegate;
	FDicePlacement OnDicePlacement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Enemy|Dices")
	TArray<TObjectPtr<ABaseDice>> EnemyDicesOnHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Enemy|Dices")
	TArray<TObjectPtr<ABaseDice>> EnemyDicesOnTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Dices")
	TArray<TObjectPtr<ABaseDice>> PlayerDicesOnTable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Enemy|Dices")
	TArray<FVector> DicesSpots;
	
	UFUNCTION()
	void GetHit() const;
	UFUNCTION()
	void DestroyFangsOnTable();	
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category= "Enemy|Booleans")
	bool bEnemyCanChooseDiceForBrawl;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category= "Enemy|Booleans")
	bool bEnemyDiceRolled;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category= "Enemy|Booleans")
	bool bIsEnemyOnSpot;

	UFUNCTION()
	void ResetDicesPosition();
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category= "Enemy|Booleans")
	bool bAreAllDicesStopped = false;

	UFUNCTION(BlueprintCallable)
	void TableHit();

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBehaviorTree> BTEnemy;

	UPROPERTY(EditDefaultsOnly, Category= "Enemy|Dices")
	int EnemyDicesNum;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Player")
	TObjectPtr<class ABasePlayer> Player;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Dialogue")
	TObjectPtr<class ADialogueManager> DialogueManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Components")
	TObjectPtr<class UHealthComponent> EnemyHealthComp;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Enemy|Components")
	TObjectPtr<class UEnemyDiceComponent> EnemyDiceComp;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Enemy|Components")
	TObjectPtr<class UEnemyDecisionComponent> EnemyDecisionComp;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Components")
	TSubclassOf<UEnemyDecisionComponent> DecisionComponentToSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Components|Strategy")
	FName StrategyName;

	UPROPERTY(VisibleAnywhere)
	bool bWasTableHit;
	UPROPERTY(VisibleAnywhere)
	int32 TableHitCount = 0;
	
	UFUNCTION(BlueprintCallable)
	virtual void PlaceDiceOnTable();
	UFUNCTION(BlueprintCallable)
	virtual void EnemyDiceRolling();

	UFUNCTION(BlueprintCallable)
	virtual void EnemySpawnDices();
	UPROPERTY(EditDefaultsOnly, Category= "Enemy|Dices")
	TArray<TSubclassOf<ABaseDice>> DicesToSpawn;
	
	UFUNCTION()
	virtual void DeathAction();

public:
	
	virtual void Tick(float DeltaTime) override;

};
