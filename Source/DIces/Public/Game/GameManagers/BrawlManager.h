

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrawlManager.generated.h"

class AGameStateBaseClass;
class UTurnManager;
class ABasePlayer;
class ABaseEnemy;
class ABaseDice;

DECLARE_DELEGATE(FRandWaiterCall);

UENUM(BlueprintType)
enum class ECurrentState : uint8
{
	Waiting				UMETA(DisplayName = "Waiting"),
	DicePlacement		UMETA(DisplayName = "DicePlacement"),
	WaiterServe			UMETA(DisplayName = "WaiterServe"),
	ScoreResolve		UMETA(DisplayName = "ScoreResolve"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UBrawlManager : public UActorComponent
{
	GENERATED_BODY()

public:	

	UBrawlManager();
	
	FRandWaiterCall RandWaiterCall;

	UFUNCTION()
	void Initialize(AGameStateBaseClass *InGameState, ABasePlayer* InPlayer, UTurnManager* InTurnManager);
	UFUNCTION()
	void InitializeEnemy(ABaseEnemy* InEnemy) { Enemy = InEnemy; }
	
	UFUNCTION()
	void SetWaiterState() { CurrentState = ECurrentState::WaiterServe; }
	UFUNCTION()
	ECurrentState GetCurrentState() const { return CurrentState; }
	
	UFUNCTION()
	void SetNewEnemy() { bIsNewEnemy = true; }
	
	UFUNCTION()
	void StartTurn();
	UFUNCTION()
	void EndTurn();
	
	void DicesPlacementSequence(ABaseDice* PlacedDice);
	
	UFUNCTION(BlueprintCallable)
	void CheckingResults();
	UFUNCTION(BlueprintCallable)
	void ResetSettings();
	UFUNCTION(BlueprintCallable)
	void ResetDicesPosition();
	void ResetPoints();
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	ECurrentState CurrentState;
	
	UPROPERTY(VisibleAnywhere)
	bool bIsPlayerFirst;
	UPROPERTY()
	bool bIsNewEnemy;
	
	UPROPERTY()
	int DicePlaced = 0;
	UFUNCTION()
	void SetPlacement(bool CanPlayerChoose, bool CanEnemyChoose, bool CanPlayerMove);
	
	UPROPERTY()
	TArray<int> SwapPoints = {2, 6, 10};
	
	UPROPERTY()
	AGameStateBaseClass *GameState;
	UPROPERTY()
	UTurnManager* TurnManager;
	UPROPERTY(VisibleAnywhere)
	ABasePlayer* Player;
	UPROPERTY(VisibleAnywhere)
	ABaseEnemy* Enemy;
	
	UPROPERTY(VisibleAnywhere)
	int BigPlayerPoints;
	UPROPERTY(VisibleAnywhere)
	int BigEnemyPoints;
	
	UPROPERTY(VisibleAnywhere, Category = "Results")
	TArray<int> EnemyResults;
	UPROPERTY(VisibleAnywhere, Category = "Results | Bonuses")
	TArray<int> EnemyBonus;
	UPROPERTY(VisibleAnywhere, Category = "Results")
	TArray<int> PlayerResults;
	UPROPERTY(VisibleAnywhere, Category = "Results | Bonuses")
	TArray<int> PlayerBonus;
	
public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
