
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueSystem/DialogueData.h"
#include "DialogueWidget.generated.h"


UCLASS()
class DICES_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue")
	void UpdateDialogue(const FText& Speaker, const FText& Body, const TArray<FDialogueChoice>& Choices, bool bHasChoices);
	
	UFUNCTION()
	void SetDialogueManager(ADialogueManager* Manager) { DialogueManager = Manager; }
	
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	TObjectPtr<ADialogueManager> DialogueManager;
};
