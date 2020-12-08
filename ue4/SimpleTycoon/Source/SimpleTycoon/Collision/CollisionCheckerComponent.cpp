#include "CollisionCheckerComponent.h"


UCollisionCheckerComponent::UCollisionCheckerComponent()
{	
	PrimaryComponentTick.bCanEverTick = false;
}

void UCollisionCheckerComponent::BeginOverlap()
{
	++AmountCollision;
}

void UCollisionCheckerComponent::EndOverlap()
{
	check(AmountCollision > 0);
	--AmountCollision;
}

uint16 UCollisionCheckerComponent::GetAmountCollision()
{
	return AmountCollision;
}

void UCollisionCheckerComponent::BeginPlay()
{
	Super::BeginPlay();
}
