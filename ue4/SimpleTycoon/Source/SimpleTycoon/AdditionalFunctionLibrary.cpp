#include "AdditionalFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


void UAdditionalFunctionLibrary::PlayProjectileFlightSound(FVector Start, FVector End, float AudibilityRadius,
	AActor* TargetActor, USoundCue* Sound)
{
	UWorld* World = TargetActor->GetWorld();
	if(!IsValid(World))
	{
		return;
	}
	
	const FVector TargetPoint = TargetActor->GetActorLocation();
	const FVector ClosesPoint =  UKismetMathLibrary::FindClosestPointOnSegment(TargetPoint, Start, End);
	const float DistanceToClosesPoint = FVector::Distance(TargetPoint, ClosesPoint);
		
	if(DistanceToClosesPoint > AudibilityRadius)
	{
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(World, Sound, ClosesPoint);	
}
