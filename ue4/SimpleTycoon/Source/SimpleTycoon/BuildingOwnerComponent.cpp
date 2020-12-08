#include "BuildingOwnerComponent.h"
#include "SimpleTycoon/Production/ProductionComponent.h"
#include "STPlayerController.h"

UBuildingOwnerComponent::UBuildingOwnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBuildingOwnerComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if(!IsValid(Owner))
	{
		return;	
	}
	UProductionComponent* ProductionComponent = Owner->FindComponentByClass<UProductionComponent>();
	if(!IsValid(ProductionComponent))
	{
		return;
	}
	ProductionComponent->OnProductionFinished.AddDynamic(this, &UBuildingOwnerComponent::EarnResource);
}

void UBuildingOwnerComponent::SetBuildingOwner(ASTPlayerController* NewBuildingOwner)
{
	BuildingOwner = NewBuildingOwner;
}

ASTPlayerController* UBuildingOwnerComponent::GetBuildingOwner() const
{
	return BuildingOwner;
}

void UBuildingOwnerComponent::EarnResource(AActor* Actor, EResourceType Product)
{
	BuildingOwner->EarnResource(Product, 1.0f);
}

