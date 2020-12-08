#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/SoundCue.h"

#include "AdditionalFunctionLibrary.generated.h"


UCLASS()
class SIMPLETYCOON_API UAdditionalFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()	
	
public:
	static void PlayProjectileFlightSound(FVector Start, FVector End, float AudibilityRadius, AActor* TargetActor, USoundCue* Sound);
};
