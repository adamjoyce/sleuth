// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "Types.h"

#include "Perception/PawnSensingComponent.h"


AEnemyCharacter::AEnemyCharacter() : LastSeenTime(0.0f),
									 LastHealthDrainTime(0.0f),
									 bSensedTarget(false),
									 SenseTimeOut(2.5f),
									 HealthDrainCooldown(0.1f),
									 HealthDrainDamage(1.0f),
									 IsVunerable(false),
									 BotType(EBotBehaviorType::Passive)
{
 	/// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// The sensing component used to detect players by visibility checks.
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SetPeripheralVisionAngle(60.0f);
	PawnSensingComponent->SightRadius = 2000;

	/// Create the visibility mesh.
	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));
	VisibleMesh->SetupAttachment(RootComponent);
	VisibleMesh->SetCollisionProfileName("NoCollision");

    /// Create the spot light for the enemy's vision cone.
    VisionCone = CreateDefaultSubobject<USpotLightComponent>(TEXT("VisionCone"));
    VisionCone->SetupAttachment(RootComponent);

	/// Populate materials.
	Materials.Init(nullptr, 2);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	/// This is the earliest moment we can bind our delegates to the component.
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePlayer);
	}

	/// Push the home location to the blackboard.
	//AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	//if (AIController)
	//{
	//	AIController->SetHomeLocation(this);
	//}
}

void AEnemyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if (AIController)
	{
		/// Check if the last time we sensed a player is beyond the time out value.
		/// Prevents the bot endlessly following the player.
		if (bSensedTarget && (GetWorld()->TimeSeconds - LastSeenTime) > SenseTimeOut)
		{
			/// Reset the target.
			bSensedTarget = false;
			AIController->SetTargetEnemy(nullptr);
            VisionCone->SetLightColor(FColor::Yellow);
		} 
	}
}

void AEnemyCharacter::OnSeePlayer(APawn* Pawn)
{
	/// Return if this enemy is dead.
	if (!IsAlive())
	{
		return;
	}

	/// Keep track of the time the player was last sensed in order to clear the target.
	bSensedTarget = true;
	LastSeenTime = GetWorld()->GetTimeSeconds();

	/// If AI Controller assigned and sensed pawn is alive, set target enemy in AI Controller.
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	ABaseCharacter* SensedPawn = Cast<ABaseCharacter>(Pawn);
	if (AIController && SensedPawn->IsAlive())
	{
		AIController->SetTargetEnemy(Pawn);
		AIController->SetTargetLocation();

		/// Start draining health.
		PerformHealthDrain(SensedPawn);
	}

	/// Set the chasing material to the sight cone.
    VisionCone->SetLightColor(FColor::Red);
}

void AEnemyCharacter::PerformHealthDrain(AActor* HitActor)
{
	/// Avoid attacking too often.
	if (LastHealthDrainTime > GetWorld()->GetTimeSeconds() - HealthDrainCooldown)
	{
		return;
	}

	if (HitActor && HitActor != this && IsAlive())
	{
		ACharacter* OtherPawn = Cast<ACharacter>(HitActor);
		if (OtherPawn)
		{
			LastHealthDrainTime = GetWorld()->GetTimeSeconds();

			FDamageEvent DamageEvent;
			HitActor->TakeDamage(HealthDrainDamage, DamageEvent, GetController(), this);

			/// Play drain animation here...
		}
	}
}

void AEnemyCharacter::SetBotType(EBotBehaviorType NewType)
{
	BotType = NewType;
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->SetBlackboardBotType(NewType);
	}
}

bool AEnemyCharacter::IsTargetSensed()
{
    return bSensedTarget;
}

void AEnemyCharacter::OnDeath()
{
	if (GetWorld())
	{

	}
}

bool AEnemyCharacter::GetIsVunerable()
{
	return IsVunerable;
}

void AEnemyCharacter::SetIsVunerable(bool Vunerable)
{
	IsVunerable = Vunerable;
}