// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"

#include "Perception/PawnSensingComponent.h"


AEnemyCharacter::AEnemyCharacter() : LastSeenTime(0.0f),
									 bSensedTarget(false),
									 SenseTimeOut(2.5f)
{
 	/// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// The sensing component used to detect players by visibility checks.
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SetPeripheralVisionAngle(60.0f);
	PawnSensingComponent->SightRadius = 2000;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/// This is the earliest moment we can bind our delegates to the component.
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePlayer);
	}
}

void AEnemyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	/// Check if the last time we sensed a player is beyond the time out value.
	/// Prevents the bot endlessly following the player.
	if (bSensedTarget && (GetWorld()->TimeSeconds - LastSeenTime) > SenseTimeOut)
	{
		AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
		if (AIController)
		{
			/// Reset the target.
			bSensedTarget = false;
			AIController->SetTargetEnemy(nullptr);
		}
	}
}

void AEnemyCharacter::OnSeePlayer(APawn* Pawn)
{
	/// If this pawn is alive...

	/// Keep track of the time the player was last sensed in order to clear the target.
	bSensedTarget = true;
	LastSeenTime = GetWorld()->GetTimeSeconds();

	/// If AI Controller assigned and sensed pawn is alive, set target enemy in AI Controller...
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->SetTargetEnemy(Pawn);
	}
}

