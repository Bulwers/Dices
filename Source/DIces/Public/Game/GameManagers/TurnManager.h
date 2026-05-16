

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurnManager.generated.h"

class ABasePlayer;
class ABaseEnemy;

UENUM(BlueprintType)
enum class ECurrentTurn : uint8
{
	Waiting			UMETA(DisplayName = "Waiting"),
	PlayerTurn		UMETA(DisplayName = "Player Turn"),
	EnemyTurn		UMETA(DisplayName = "Enemy Turn")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UTurnManager : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTurnManager();
	
	UFUNCTION()
	void WhoseFirst(bool bIsPlayerFirst);
	UFUNCTION()
	void SwapOrder();
	UFUNCTION()
	bool IsPlayerTurn() const;
	UFUNCTION()
	void SetWaitingTurn();
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	ECurrentTurn ECurrentTurn;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
