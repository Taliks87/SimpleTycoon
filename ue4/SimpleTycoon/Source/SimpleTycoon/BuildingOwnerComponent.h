#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleTycoon/Resource/ResourceType.h"

#include "BuildingOwnerComponent.generated.h"


class ASTPlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLETYCOON_API UBuildingOwnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:		
	UBuildingOwnerComponent();

protected:	
	virtual void BeginPlay() override;

public:		
	UFUNCTION(BlueprintCallable)
    void SetBuildingOwner(ASTPlayerController* NewBuildingOwner);

	UFUNCTION(BlueprintCallable)
	ASTPlayerController* GetBuildingOwner() const;

private:
	UFUNCTION()
	void EarnResource(AActor* Actor, EResourceType Product);

private:
	UPROPERTY()
	ASTPlayerController* BuildingOwner;		
};
