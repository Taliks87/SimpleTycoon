#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleTycoon/Resource/ResourceType.h"

#include "ProductionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProductionStarted, AActor*, Actor, EResourceType, Product);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProductionChanged, float, Percentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProductionFinished, AActor*, Actor, EResourceType, Product);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLETYCOON_API UProductionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UProductionComponent();

protected:	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void StartProduction(EResourceType NewProductType, float Time);
	
	UFUNCTION(BlueprintCallable)
	bool IsProducing();

public:		
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	virtual void FinishProduct();

public:
	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnProductionStarted OnProductionStarted;
	
	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnProductionChanged OnProductionChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnProductionFinished OnProductionFinished;

private:	
	EResourceType ProductType = EResourceType::Coin;
	bool bProducing = false;

	float ProducingTimeLeft = 0.0f;
	float ProducingTime = 0.0f;
};
