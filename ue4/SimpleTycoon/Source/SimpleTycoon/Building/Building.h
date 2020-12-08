#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleTycoon/STPlayerController.h"

#include "Building.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlacedBuilding);

class UCollisionCheckerComponent;

UCLASS()
class SIMPLETYCOON_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABuilding();
	
	bool IsCanByPlaced() const;
	
	void FinishPlaceBuilding(ASTPlayerController* NewOwnerPlayer) const;

	UFUNCTION()
    void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
    void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnCanByPlacedChanged(bool bCanByPlacedFlag);

protected:
	UPROPERTY(BlueprintAssignable)
	FOnPlacedBuilding OnPlacedBuilding;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings")
	class UBuildingOwnerComponent* BuildingOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bCanByPlaced = true;
	
	UPROPERTY()
	UCollisionCheckerComponent* CollisionChecker = nullptr;
};
