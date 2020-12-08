#include "Building.h"
#include "SimpleTycoon/SimpleTycoon.h"
#include "SimpleTycoon/BuildingOwnerComponent.h"
#include "SimpleTycoon/Collision/CollisionCheckerComponent.h"


ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	BuildingOwner = CreateDefaultSubobject<UBuildingOwnerComponent>(TEXT("BuildingOwner"));	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));	
	StaticMesh->SetCollisionObjectType(ECC_WorldStatic);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	StaticMesh->SetupAttachment(RootComponent);
}

bool ABuilding::IsCanByPlaced() const
{	
	return IsValid(CollisionChecker) && CollisionChecker->GetAmountCollision() == 0;
}

void ABuilding::FinishPlaceBuilding(ASTPlayerController* NewOwnerPlayer) const
{
	if(IsValid(CollisionChecker))
	{
		BuildingOwner->SetBuildingOwner(NewOwnerPlayer);
		OnPlacedBuilding.Broadcast();
		StaticMesh->OnComponentBeginOverlap.RemoveDynamic(this, &ABuilding::BeginOverlap);
		StaticMesh->OnComponentEndOverlap.RemoveDynamic(this, &ABuilding::EndOverlap);
		CollisionChecker->DestroyComponent();		
	}
	else
	{
		UE_LOG(LogST, Warning, TEXT("CollisionChecker Component is't exist"));
	}
}

void ABuilding::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(CollisionChecker->GetAmountCollision() == 0)
	{
		OnCanByPlacedChanged(false);
	}	
	CollisionChecker->BeginOverlap();		
}

void ABuilding::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	CollisionChecker->EndOverlap();
	if(CollisionChecker->GetAmountCollision() == 0)
	{
		OnCanByPlacedChanged(true);
	}
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
			
	CollisionChecker = NewObject<UCollisionCheckerComponent>(this, TEXT("CollisionChecker"));
	if(CollisionChecker)
	{
		CollisionChecker->RegisterComponent();
		StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABuilding::BeginOverlap);
		StaticMesh->OnComponentEndOverlap.AddDynamic(this, &ABuilding::EndOverlap);	
	}
	OnCanByPlacedChanged(true);
}
