// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "EnemyCharacter.h"

#include "Perception/PawnSensingComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter() : LastSeenTime(0.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// The senseing component used to detect players by visibility checks.
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SetPeripheralVisionAngle(60.0f);
	PawnSensingComponent->SightRadius = 2000;
}

// Called when the game starts or when spawned.
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/// This is the earliest moment we can bind our delegates to the component.
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePlayer);
	}
}

// Called every frame.
void AEnemyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Triggered by the pawn sensing component when a pawn is spotted.
void AEnemyCharacter::OnSeePlayer(APawn* Pawn)
{
	/// If this pawn is alive...

	/// Keep track of the time the player was last sensed in order to clear the target.
	LastSeenTime = GetWorld()->GetTimeSeconds();

	/// If AI Controller assigned and sensed pawn is alive, set target enemy in AI Controller...
}

