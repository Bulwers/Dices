

#include "Enemies/Comp/DarkvisionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CandleClass.h"
#include "Dices/BaseDice.h"
#include "Player/DicePlayerController.h"
#include "Player/Widgets/PlayerHUD.h"

UDarkvisionComponent::UDarkvisionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDarkvisionComponent::BeginPlay()
{
	Super::BeginPlay();
	InitCandleRef();
	
	PlayerController = Cast<ADicePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController) PlayerHUD = Cast<UPlayerHUD>(PlayerController->PlayerWidget);
	if (PlayerHUD) PlayerHUD->EndTurnDelegate.AddUObject(this, &UDarkvisionComponent::EndTurn);
}

void UDarkvisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDarkvisionComponent::InitCandleRef()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Extinguishable"), FoundActors);
	
	if (FoundActors.Num() > 0) CandleRef = Cast<ACandleClass>(FoundActors[0]);
	if (CandleRef)
	{
		bIsCandleExtinguished = CandleRef->IsCandleExtinguished();
		CandleRef->OnLightSwitch.BindUObject(this, &UDarkvisionComponent::SwapbCanSwapDices);
	}
}

void UDarkvisionComponent::LightsOut()
{
	if (!CandleRef) return;
	if (CandleRef->IsCandleExtinguished()) return;
	CandleRef->OnExtinguishedLight();
}

void UDarkvisionComponent::SwapDices(
	UPARAM(ref) TArray<ABaseDice*>& EnemyDicesOnTable, 
	const TArray<ABaseDice*>& PlayerDicesOnTable, 
	const TArray<FVector>& Spots)
{
	if (!bIsCandleExtinguished) return;
	if (bIsSwapped) return;
	
	const int Size = EnemyDicesOnTable.Num();
	for (int A = 0; A < Size; A++)
	{
		if (!PlayerDicesOnTable[A] || !EnemyDicesOnTable[A]) continue;
		//if (EnemyDicesOnTable[A]->Sum() - PlayerDicesOnTable[A]->Sum() > 1) continue;
	
		for (int B = 0; B < Size; B++)
		{
			if (A == B) continue;
			if (!EnemyDicesOnTable[B] || !PlayerDicesOnTable[B]) continue;
			if (EnemyDicesOnTable[A]->Sum() == EnemyDicesOnTable[B]->Sum()) continue;
			if (PlayerDicesOnTable[A]->Sum() == PlayerDicesOnTable[B]->Sum()) continue;
			UE_LOG(LogTemp, Warning, TEXT("A=%d B=%d"), A, B);
			
			TArray<int32> ResultsBefore;
			ResultsBefore.Add(EnemyDicesOnTable[A]->Sum() - PlayerDicesOnTable[A]->Sum());
			ResultsBefore.Add(EnemyDicesOnTable[B]->Sum() - PlayerDicesOnTable[B]->Sum());
			TArray<int32> ResultsAfter;
			ResultsAfter.Add(EnemyDicesOnTable[B]->Sum() - PlayerDicesOnTable[A]->Sum());
			ResultsAfter.Add(EnemyDicesOnTable[A]->Sum() - PlayerDicesOnTable[B]->Sum());
			
			int32 PlayerPointsBefore = 0;
			int32 EnemyPointsBefore = 0;
			
			for (int i : ResultsBefore)
			{
				if (i <= -2) PlayerPointsBefore++;
				else if (i >= 2) EnemyPointsBefore++;
			}
			
			int32 PlayerPointsAfter = 0;
			int32 EnemyPointsAfter = 0;
			
			for (int i : ResultsAfter)
			{
				if (i <= -2) PlayerPointsAfter++;
				else if (i >= 2) EnemyPointsAfter++;
			}
			
			if (EnemyPointsAfter > EnemyPointsBefore && PlayerPointsAfter <= PlayerPointsBefore)
			{
				EnemyDicesOnTable[A]->DiceMesh->SetRelativeLocation(FVector(10, 0, 0), false, nullptr, ETeleportType::None);
				
				Swap(EnemyDicesOnTable[A], EnemyDicesOnTable[B]);

				EnemyDicesOnTable[A]->DiceMesh->SetWorldLocation(Spots[A], false, nullptr, ETeleportType::None);
				EnemyDicesOnTable[B]->DiceMesh->SetWorldLocation(Spots[B], false, nullptr, ETeleportType::None);
				UE_LOG(LogTemp, Warning, TEXT("Dices Swapped"));
				bIsSwapped = true;
				return;
			}
		}
	}
}