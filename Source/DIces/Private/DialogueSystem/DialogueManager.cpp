
#include "DialogueSystem/DialogueManager.h"
#include "Blueprint/UserWidget.h"
#include "DialogueSystem/DialogueWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

ADialogueManager::ADialogueManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADialogueManager::BeginPlay()
{
	Super::BeginPlay();
}

void ADialogueManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADialogueManager::StartDialogue(UDialogueData* Data)
{
	if (!Data || Data->DialogueLines.Num() == 0) return;
	
	CurrentDialogue = Data;
	CurrentLineIndex = 0;
	
	if (DialogueWidgetClass && !DialogueWidget)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		DialogueWidget = CreateWidget<UDialogueWidget>(PC, DialogueWidgetClass);
		DialogueWidget->SetDialogueManager(this);
		DialogueWidget->AddToViewport();
	}
	ShowLine(0);
}

void ADialogueManager::ShowLine(int32 Index)
{
	
	if (!CurrentDialogue || !CurrentDialogue->DialogueLines.IsValidIndex(Index))
	{
		EndDialogue();
		return;
	}

	CurrentLineIndex = Index;
	const FDialogueLine& Line = CurrentDialogue->DialogueLines[Index];

	if (DialogueWidget)
	{
		FName FunctionName = "UpdateDialogue";
		UFunction* Function = DialogueWidget->FindFunction(FunctionName);
		if (Function)
		{
			struct { FText Speaker; FText Body; TArray<FDialogueChoice> Choices; bool bHasChoices; } Parameters;
			Parameters.Speaker = Line.SpeakerName;
			Parameters.Body = Line.DialogueText;
			Parameters.Choices = Line.Choices;
			Parameters.bHasChoices = true;
			if (Line.Choices.IsEmpty()) Parameters.bHasChoices = false;
			DialogueWidget->ProcessEvent(Function, &Parameters);
		}
	}
}

void ADialogueManager::Continue()
{
	if (!CurrentDialogue || !CurrentDialogue->DialogueLines.IsValidIndex(CurrentLineIndex)) return;

	const FDialogueLine& Line = CurrentDialogue->DialogueLines[CurrentLineIndex];

	if (Line.NextLineIndex == -1)
		EndDialogue();
	else
		ShowLine(Line.NextLineIndex);
}

void ADialogueManager::SelectChoice(int32 ChoiceIndex)
{
	if (!CurrentDialogue || !CurrentDialogue->DialogueLines.IsValidIndex(CurrentLineIndex)) return;

	const FDialogueLine& Line = CurrentDialogue->DialogueLines[CurrentLineIndex];

	if (!Line.Choices.IsValidIndex(ChoiceIndex)) return;

	int32 Next = Line.Choices[ChoiceIndex].NextLineIndex;

	if (Next == -1)
		EndDialogue();
	else
		ShowLine(Next);
}

void ADialogueManager::EndDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
	}
	OnDialogueEnd.Broadcast();
}