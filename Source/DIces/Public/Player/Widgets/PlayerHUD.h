

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PlayerHUD.generated.h"

DECLARE_MULTICAST_DELEGATE(FEndTurnDelegate);
DECLARE_DELEGATE(FDismissDelegate);

UCLASS()
class DICES_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	FEndTurnDelegate EndTurnDelegate;
	FDismissDelegate DismissDelegate;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> EndTurnButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> DismissButton;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AGameStateBaseClass> GameState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class ABasePlayer> Player;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AWaiter> Waiter;
	
	UFUNCTION(BlueprintCallable)
	void EndTurn() { EndTurnDelegate.Broadcast(); };

	UFUNCTION(BlueprintCallable)
	void WaiterDismissButton() { DismissDelegate.ExecuteIfBound(); };

};
