#include "STPlayerController.h"

#include "DrawDebugHelpers.h"
#include "SimpleTycoon.h"
#include "Building/ConstructionCursorComponent.h"
#include "SimpleTycoon/Building/Building.h"

ASTPlayerController::ASTPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;

	ConstructionCursorComponent = CreateDefaultSubobject<UConstructionCursorComponent>(TEXT("ConstructionCursor"));	
}

void ASTPlayerController::BeginPlay()
{
	ConstructionCursorComponent->Init(this);
	for (uint8 Val = 0; Val < static_cast<uint8>(EResourceType::Max); ++Val)
	{		
		Resources.Add(100.0f);				
	}	
}

void ASTPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(ControlMode == EControlMode::Build)
	{		
		const FVector NewPositionForBuilding = GetCursorLocationByChannel(LandscapeChannel);
		if(!NewPositionForBuilding.IsZero())
		{
			ConstructionCursorComponent->UpdateCursorLocation(NewPositionForBuilding);			
		}
	}
}

float ASTPlayerController::GetResource(EResourceType Type)
{
	return Resources[static_cast<uint8>(Type)];
}

void ASTPlayerController::RequestToBuyBuilding(TSubclassOf<ABuilding> BuildingType)
{
	if (ControlMode != EControlMode::Selection)
	{
		return;
	}
	BuildingData = BuildingsDataList.Find(BuildingType);
	if(!BuildingData)
	{		
		return;
	}	
	if(IsEnoughResources(BuildingData->ResourceType, BuildingData->Cost))
	{		
		if(ConstructionCursorComponent->TryStartChoosePlace(BuildingType, GetCursorLocationByChannel(LandscapeChannel)))
		{
			ControlMode = EControlMode::Build;			 
		}		
	}
	else
	{				
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,  TEXT("Need more resource for buy " + BuildingType->GetDisplayNameText().ToString()) );
	}
}

void ASTPlayerController::EarnResource(EResourceType Type, float Value)
{
	if(Value < 0.0f)
	{
		UE_LOG(LogST, Warning, TEXT("Incorrect amount of resources earned"));
		return;
	}

	float& Resource = Resources[static_cast<uint8>(Type)];
	Resource += Value;
	OnResourceChanged(Type, Resource);
}

bool ASTPlayerController::TrySpendResource(EResourceType Type, float Value)
{
	if(Value < 0.0f)
	{
		UE_LOG(LogST, Warning, TEXT("Incorrect amount of resources spent"));
		return false;
	}
	float& Resource = Resources[static_cast<uint8>(Type)];
	if(IsEnoughResources(Type, Value))
	{
		Resource -= Value;
		OnResourceChanged(Type, Resource);
		return true;	
	}
	return false;
}

bool ASTPlayerController::IsEnoughResources(EResourceType Type, float Value)
{
	if(Value < 0.0f)
	{		
		return false;
	}
	float& Resource = Resources[static_cast<uint8>(Type)];
	if(Resource < Value)
	{
		return false;
	}
	return true;
}

FVector ASTPlayerController::GetCursorLocationByChannel(TEnumAsByte<ECollisionChannel> Channel)
{
	UWorld* World = GetWorld();
	if(!World)
	{
		return FVector::ZeroVector;
	}
	
	//Get cursor location
	FVector CursorLocation;
	FVector CursorDirection;
	DeprojectMousePositionToWorld(CursorLocation, CursorDirection);
	const FVector End = CursorLocation + CursorDirection * MaxInteractDistance;

	//Detect cursor hit	
	FCollisionQueryParams TraceParams;
	const APawn* PlayerPawn = GetPawn();		
	TraceParams.AddIgnoredActor(PlayerPawn);						
	FHitResult OutHit;
		
	World->LineTraceSingleByChannel(OutHit, CursorLocation, End, Channel, TraceParams);
	
	if(OutHit.bBlockingHit)
	{			
		return OutHit.ImpactPoint;						
	}			
	
	return FVector::ZeroVector;
}

void ASTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("ConstructBuilding"), IE_Released, this, &ASTPlayerController::ConstructBuilding);
	InputComponent->BindAction(TEXT("CancelConstruction"), IE_Released, this, &ASTPlayerController::CancelConstruction);
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ASTPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ASTPlayerController::MoveRight);
}

void ASTPlayerController::MoveForward(float Value)
{
	if(Value != 0.0)
	{
		APawn* PlayerPawn = GetPawnOrSpectator();

		if (!PlayerPawn)
		{
			return;
		}
		PlayerPawn->SetActorLocation(PlayerPawn->GetActorLocation() + FVector::ForwardVector * Value * CameraSpeed);		
	}
}

void ASTPlayerController::MoveRight(float Value)
{
	if(Value != 0.0)
	{
		APawn* PlayerPawn = GetPawnOrSpectator();

		if (!PlayerPawn)
		{
			return;
		}
		PlayerPawn->SetActorLocation(PlayerPawn->GetActorLocation() + FVector::RightVector * Value * CameraSpeed);
	}
}

void ASTPlayerController::ConstructBuilding()
{
	if (ControlMode != EControlMode::Build)
	{
		return;
	}
	if(IsEnoughResources(BuildingData->ResourceType, BuildingData->Cost))
	{
		if(ConstructionCursorComponent->TryFinishChoosePlace())
		{
			TrySpendResource(BuildingData->ResourceType, BuildingData->Cost);
			ControlMode = EControlMode::Selection;
		}
	}
}

void ASTPlayerController::CancelConstruction()
{
	if (ControlMode != EControlMode::Build)
	{
		return;
	}
	ConstructionCursorComponent->CancelChoosePlace();
	ControlMode = EControlMode::Selection;
}