

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateBaseClass.generated.h"

class UTurnManager;
class UBrawlManager;
class UWaiterManager;
class ABasePlayer;
class ABaseEnemy;
class ABaseDice;

UCLASS()
class DICES_API AGameStateBaseClass : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	AGameStateBaseClass();
	
	UFUNCTION()
	void TurnCountIncrease() { TurnCount++; }
	UFUNCTION()
	int GetTurnCount() const { return TurnCount; }
	UFUNCTION()
	int GetEnemiesCount() const { return EnemiesCount; }
	
	UFUNCTION()
	ABasePlayer* GetPlayer() const { return Player; }
	UFUNCTION()
	ABaseEnemy* GetEnemy() const { return Enemy; }

	UFUNCTION(BlueprintCallable)
	UWaiterManager* GetWaiterManager() const { return WaiterManager; }
	UFUNCTION(BlueprintCallable)
	UBrawlManager* GetBrawlManager() const { return BrawlManager; }
	UFUNCTION(BlueprintCallable)
	UTurnManager* GetTurnManager() const { return TurnManager; }

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<ABasePlayer> Player;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseEnemy> Enemy;

	UPROPERTY(VisibleAnywhere)
	int TurnCount = 1;
	UPROPERTY(VisibleAnywhere)
	int EnemiesCount = 0;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTurnManager> TurnManager;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBrawlManager> BrawlManager;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWaiterManager> WaiterManager;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ABaseEnemy>> EnemiesToSpawn;
	UPROPERTY(EditAnywhere)
	FVector EnemySpawnLoc;
	UPROPERTY(EditAnywhere)
	FRotator EnemySpawnRot;
	
	UFUNCTION(BlueprintCallable)
	void EnemyReset();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class ACandleClass> Candle;
	
	void PlayerCameraBlock();
	UPROPERTY()
	bool bCameraBlock;

	int RandEnemy();
	void TableHitCheck();

public:

	virtual void Tick(float DeltaTime) override;
};
