

#include "Enemies/Comp/DarkvisionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CandleClass.h"
#include "Enemies/BaseEnemy.h"

UDarkvisionComponent::UDarkvisionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDarkvisionComponent::BeginPlay()
{
	Super::BeginPlay();
	InitCandleRef();
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
	if (CandleRef->IsCandleExtinguished()) bCanSwapDices = true;
	if (CandleRef) CandleRef->OnLightSwitch.BindUObject(this, &UDarkvisionComponent::SwapbCanSwapDices);
}

void UDarkvisionComponent::LightsOut()
{
	if (!CandleRef) return;
	CandleRef->OnExtinguishedLight();
}

void UDarkvisionComponent::SwapDices(ABaseEnemy* Owner)
{
	if (!bCanSwapDices) return;
	bool bSwapped = false;
	TArray Spots {
		FVector(5, -25, 97),
		FVector(5, -15, 97),
		FVector(5, -5, 97),
		FVector(5, 5, 97),
		FVector(5, 15, 97),
		FVector(5, 25, 97)
	};
	for (int A = 0; A <= 5; A++) 
	{
		if (!Owner->PlayerDicesOnTable[A] || !Owner->EnemyDicesOnTable[A]) continue;
		if (Owner->EnemyDicesOnTable[A]->Result() - Owner->PlayerDicesOnTable[A]->Result() > 1) continue;
	
		for (int B = 0; B <= 5; B++)
		{
			if (A == B) continue;
			if (Owner->EnemyDicesOnTable[A]->Result() - Owner->PlayerDicesOnTable[B]->Result() >= -1 && 
				Owner->EnemyDicesOnTable[B]->Result() - Owner->PlayerDicesOnTable[A]->Result() >= -1)
			{
				Owner->EnemyDicesOnTable[A]->DiceMesh->SetRelativeLocation(FVector(10, 0, 0), false, nullptr, ETeleportType::None);
				
				Swap(Owner->EnemyDicesOnTable[A], Owner->EnemyDicesOnTable[B]);

				Owner->EnemyDicesOnTable[A]->DiceMesh->SetWorldLocation(Spots[B], false, nullptr, ETeleportType::None);
				Owner->EnemyDicesOnTable[B]->DiceMesh->SetWorldLocation(Spots[A], false, nullptr, ETeleportType::None);
				bSwapped = true;
				break;
			}
		}
		if (bSwapped) break;
	}
}