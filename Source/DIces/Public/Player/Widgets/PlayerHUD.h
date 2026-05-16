

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PlayerHUD.generated.h"

UCLASS()
class DICES_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* EndTurnButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* DismissButton;
	
	UPROPERTY(BlueprintReadOnly)
	class AGameStateBaseClass* GameState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABasePlayer* Player;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AWaiter* Waiter;
	
	UFUNCTION(BlueprintCallable)
	void EndTurn();

	UFUNCTION(BlueprintCallable)
	void WaiterDismissButton();

};
