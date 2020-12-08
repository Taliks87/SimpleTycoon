#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"

#include "ProductionProgressBarComponent.generated.h"


UCLASS()
class SIMPLETYCOON_API UProductionProgressBarComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UProductionProgressBarComponent();
protected:
	virtual void BeginPlay() override;	

	UFUNCTION(BlueprintImplementableEvent)
    void OnUpdateProgressBar(float Percentage);

private:
	UFUNCTION()
	void UpdateProgressBar(float Percentage);
};
