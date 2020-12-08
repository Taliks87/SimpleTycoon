#include "ProductionProgressBarComponent.h"

#include "ProductionComponent.h"
#include "SimpleTycoon/AdditionalFunctionLibrary.h"


UProductionProgressBarComponent::UProductionProgressBarComponent()
	: UWidgetComponent()
{
	Space = EWidgetSpace::Screen;
	PrimaryComponentTick.bCanEverTick = true;
}

void UProductionProgressBarComponent::BeginPlay()
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

	ProductionComponent->OnProductionChanged.AddDynamic(this, &UProductionProgressBarComponent::UpdateProgressBar);
}

void UProductionProgressBarComponent::UpdateProgressBar(float Percentage)
{
	OnUpdateProgressBar(Percentage);
}
