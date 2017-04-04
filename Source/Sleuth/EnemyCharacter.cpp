// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "PlayerCharacter.h"
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
									 IsVulnerable(false),
									 VulnerableEmissionValue(10.0f),
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

	/// Create the weak zone at the back of the enemy.
	WeakZone = CreateDefaultSubobject<UBoxComponent>(TEXT("WeakZone"));
	WeakZone->SetRelativeScale3D(FVector(1.0f, 0.1f, 0.1f));
	WeakZone->SetRelativeLocation(FVector(-83.0f, 0.0f, 0.0f));
	WeakZone->SetupAttachment(RootComponent);

    /// Create the spot light for the enemy's vision cone.
    VisionCone = CreateDefaultSubobject<USpotLightComponent>(TEXT("VisionCone"));
    VisionCone->SetupAttachment(RootComponent);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	/// This is the earliest moment we can bind our delegates to the component.
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePlayer);
	}

	if (WeakZone)
	{
		WeakZone->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapBegin);
		WeakZone->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapEnd);
	}

	/// TODO: Check that the material interface isn't always initiliased to something other than null.
	/// Might be after 'VisibleMesh->GetMaterial(0)->GetMaterial()'.
	if (VisibleMesh->GetMaterial(0) != nullptr)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(VisibleMesh->GetMaterial(0), this);
		VisibleMesh->SetMaterial(0, DynamicMaterial);
	}
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

void AEnemyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetWorld())
	{
		/// Triggering actor is not this actor and a player character.
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass(UStaticMeshComponent::StaticClass())))
		{
			/// Make enemy character vulnerable.
			SetIsVulnerable(true);

			if (VisibleMesh->GetMaterial(0) != nullptr)
			{
				/// Enable vulnerability 'glow'.
				DynamicMaterial->SetScalarParameterValue("EmissiveBrightness", VulnerableEmissionValue);
				UE_LOG(LogTemp, Warning, TEXT("ENTER"));
			}
		}
	}
}

void AEnemyCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (GetWorld())
	//{
	//	/// Triggering actor is not this actor and a player character.
	//	/// NOTE: Probably a better way to check if the object has died and access violations will occur.
	//	if (OtherActor != nullptr && OtherActor != this && OtherComp == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass(UStaticMeshComponent::StaticClass()))
	//	{
	//		/// Make enemy character vulnerable.
	//		SetIsVulnerable(false);

	//		if (VisibleMesh->GetMaterial(0) != nullptr)
	//		{
	//			/// Enable vulnerability 'glow'.
	//			DynamicMaterial->SetScalarParameterValue("EmissiveBrightness", 1.0f);
	//			UE_LOG(LogTemp, Warning, TEXT("LEAVE"));
	//		}
	//	}
	//}
}

bool AEnemyCharacter::GetIsVulnerable()
{
	return IsVulnerable;
}

void AEnemyCharacter::SetIsVulnerable(bool Vunerable)
{
	IsVulnerable = Vunerable;
}