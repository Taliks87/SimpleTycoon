// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SimpleTycoon/Resource/ResourceType.h"

#include "STPlayerController.generated.h"

class ABuilding;

UENUM(BlueprintType)
enum EControlMode
{
	Selection = 0,
	Build
};

USTRUCT(BlueprintType)
struct FBuildingData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EResourceType ResourceType = EResourceType::Coin;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cost = 10.0f;
};

class UConstructionCursorComponent;

UCLASS()
class SIMPLETYCOON_API ASTPlayerController : public APlayerController
{
private:
	GENERATED_BODY()

public:
	ASTPlayerController();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	float GetResource(EResourceType Type);

	UFUNCTION(BlueprintCallable)
    void RequestToBuyBuilding(TSubclassOf<ABuilding> BuildingType);

	UFUNCTION(BlueprintCallable)
    void EarnResource(EResourceType Type, float Value);
	
	UFUNCTION(BlueprintCallable)
    bool TrySpendResource(EResourceType Type, float Value);

	UFUNCTION(BlueprintCallable)
    bool IsEnoughResources(EResourceType Type, float Value);	
	
	UFUNCTION(BlueprintCallable)
    FVector GetCursorLocationByChannel(TEnumAsByte<ECollisionChannel> Channel);

	UFUNCTION(BlueprintImplementableEvent)
	void OnResourceChanged(EResourceType Type, float Value); 

protected:
	virtual void SetupInputComponent() override;

private:
	UFUNCTION()
    void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);
	
	UFUNCTION()
	void ConstructBuilding();

	UFUNCTION()
	void CancelConstruction();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(UIMin = 5.0f, UIMax = 50.0f))
	float CameraSpeed = 20.0f;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Sattings")
	TEnumAsByte<ECollisionChannel> LandscapeChannel = ECC_GameTraceChannel1;
	
	UPROPERTY(EditDefaultsOnly, Category="Sattings")
	TMap<TSubclassOf<AActor>, FBuildingData> BuildingsDataList;

	UPROPERTY(VisibleAnywhere)
	UConstructionCursorComponent* ConstructionCursorComponent;

	UPROPERTY()
	TArray<float> Resources;
	
	EControlMode ControlMode = EControlMode::Selection;	
	float MaxInteractDistance = 20000.0f;

	FBuildingData* BuildingData;		
};
