#include "ConstructionCursorComponent.h"
#include "SimpleTycoon/SimpleTycoon.h"
#include "SimpleTycoon/Building/Building.h"


UConstructionCursorComponent::UConstructionCursorComponent()
{	
	PrimaryComponentTick.bCanEverTick = false;	
}

void UConstructionCursorComponent::Init(ASTPlayerController* NewOwnerPlayer)
{
	OwnerPlayer = NewOwnerPlayer;
}

void UConstructionCursorComponent::BeginPlay()
{
	Super::BeginPlay();	 
}

bool UConstructionCursorComponent::TryStartChoosePlace(TSubclassOf<ABuilding> BuildingType, FVector BuildingLocation)
{			
	const FActorSpawnParameters SpawnParameters;
	ConstructionBuilding = GetWorld()->SpawnActor<ABuilding>(BuildingType, BuildingLocation, FRotator::ZeroRotator, SpawnParameters);	
	return ConstructionBuilding != nullptr;
}

void UConstructionCursorComponent::UpdateCursorLocation(FVector BuildingLocation)
{
	if(IsValid(ConstructionBuilding))
	{
		ConstructionBuilding->SetActorLocation(BuildingLocation + FVector::UpVector * 100.0f);
	}
	else
	{
		UE_LOG(LogST, Warning, TEXT("Construction building is absent"));
	}
}

bool UConstructionCursorComponent::TryFinishChoosePlace()
{
	if(!ConstructionBuilding->IsCanByPlaced())
	{
		return false;
	}
	if(IsValid(OwnerPlayer))
	{
		ConstructionBuilding->SetActorLocation(ConstructionBuilding->GetActorLocation() - FVector::UpVector * 100.0f);
		ConstructionBuilding->FinishPlaceBuilding(OwnerPlayer);			
	}
	else
	{
		UE_LOG(LogST, Warning, TEXT("Owner player os absent"))
		return false;
	}		

	return true;
}

void UConstructionCursorComponent::CancelChoosePlace() const
{
	ConstructionBuilding->Destroy();
}
