// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "EnemyActor.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values.
AEnemyActor::AEnemyActor() : MoveSpeed(300.0f),
							 WanderTarget(FVector(0.0f, 0.0f, 0.0f))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root component to deal with physics interactions.
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;

	// Setup a visible mesh component.
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	CubeMesh->SetupAttachment(RootComponent);

	// Line of sight vision cone component.
	VisionCone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LOSMesh"));
	VisionCone->SetupAttachment(RootComponent);
	VisionCone->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned.
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame.
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WanderRadius = 2.0f;
	float WanderDistance = 20.0f;
	float Jitter = 10.0f;

	// Get a random 2D vector direction.
	WanderTarget += FVector(RandomBinomial() * Jitter, RandomBinomial() * Jitter, 0.0f);
	WanderTarget = WanderTarget.GetSafeNormal2D();
	WanderTarget *= WanderRadius;

	FVector TargetInLocalSpace = WanderTarget + FVector(WanderDistance, 0.0f, 0.0f);
	FVector TargetInWorldSpace = UKismetMathLibrary::TransformLocation(RootComponent->GetComponentTransform(), TargetInLocalSpace);
	TargetInWorldSpace -= GetActorLocation();
	TargetInWorldSpace = TargetInWorldSpace.GetSafeNormal2D();

	FVector Movement = TargetInWorldSpace * MoveSpeed * DeltaTime;
	FHitResult Hit(1.0f);
	RootComponent->MoveComponent(Movement, Movement.Rotation(), true, &Hit);
}

// Generates a random binomial between -1.0f and 1.0f with a imbalance towards 0.0f.
const float AEnemyActor::RandomBinomial()
{
	return FMath::RandRange(0.0f, 1.0f) - FMath::RandRange(0.0f, 1.0f);
}

