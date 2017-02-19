// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "EnemyActor.h"


// Sets default values.
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root component to deal with physics interactions.
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;

	// Setup a visible mesh component.
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMeshComponent"));
	CubeMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned.
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame.
void AEnemyActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

