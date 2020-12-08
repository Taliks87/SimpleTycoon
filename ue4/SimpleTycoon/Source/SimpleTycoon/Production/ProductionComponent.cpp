#include "ProductionComponent.h"

#include "SimpleTycoon/SimpleTycoon.h"


UProductionComponent::UProductionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UProductionComponent::BeginPlay()
{	
	Super::BeginPlay();
}

void UProductionComponent::StartProduction(EResourceType NewProductType, float Time)
{
	if(IsProducing())
	{
		UE_LOG(LogST, Warning, TEXT("Can't start prodaction in %s"), *GetOwner()->GetName());
		return;
	}

	bProducing = true;
	ProductType = NewProductType;
	ProducingTimeLeft = Time;
	ProducingTime = Time;
	OnProductionStarted.Broadcast(GetOwner(), ProductType);	
}

bool UProductionComponent::IsProducing()
{
	return bProducing;
}

void UProductionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(!IsProducing())
	{
		return;
	}
	ProducingTimeLeft -= DeltaTime;	

	if(ProducingTimeLeft < 0.0f)
	{
		ProducingTimeLeft = 0.0f;
	}
	
	OnProductionChanged.Broadcast(1.0f - ProducingTimeLeft/ProducingTime);
	
	if(ProducingTimeLeft == 0.0f)
	{		
		FinishProduct();		
	}				
}

void UProductionComponent::FinishProduct()
{	
	bProducing = false;
	ProducingTimeLeft = 0.0f;
	OnProductionFinished.Broadcast(GetOwner(), ProductType);	
}

