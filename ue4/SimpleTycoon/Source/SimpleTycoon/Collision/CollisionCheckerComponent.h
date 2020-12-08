#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionCheckerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLETYCOON_API UCollisionCheckerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCollisionCheckerComponent();
	
	void BeginOverlap();
	
	void EndOverlap();
	
	uint16 GetAmountCollision();

protected:	
	virtual void BeginPlay() override;
	
private:
	uint16 AmountCollision;
};
