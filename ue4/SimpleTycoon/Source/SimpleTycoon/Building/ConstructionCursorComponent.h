#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConstructionCursorComponent.generated.h"

class ASTPlayerController;
class ABuilding;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLETYCOON_API UConstructionCursorComponent : public UActorComponent
{
	GENERATED_BODY()

public:		
	UConstructionCursorComponent();

	void Init(ASTPlayerController* NewOwnerPlayer);
	
    bool TryStartChoosePlace(TSubclassOf<ABuilding> BuildingType, FVector BuildingLocation);
	void UpdateCursorLocation(FVector BuildingLocation);
	bool TryFinishChoosePlace();
	void CancelChoosePlace() const;
	
protected:	
	virtual void BeginPlay() override;

private:	
	UPROPERTY()
	class ABuilding* ConstructionBuilding = nullptr;

	UPROPERTY()
	ASTPlayerController* OwnerPlayer;
};
