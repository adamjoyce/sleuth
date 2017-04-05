// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter() : Health(100.0f)
								   //IsDying(false)
{
 	/* Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it. */
	PrimaryActorTick.bCanEverTick = true;
}

float ABaseCharacter::GetHealth() const
{
	return Health;
}

bool ABaseCharacter::IsAlive() const
{
	return Health > 0;
}

float ABaseCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (Health <= 0.0f)
	{
		return 0.0f;
	}

	const float DamageToTake = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (DamageToTake > 0.0f)
	{
		Health -= DamageToTake;

		if (Health <= 0.0f)
		{
			/// Stick dying code in here...
			/// Maybe place checks to see if dying is possible...
			OnDeath();
		}
	}

	return DamageToTake;
}

void ABaseCharacter::OnDeath()
{
	/// By default simply destroy the actor.
	//if (GetWorld())
	//{
	//	GetWorld()->DestroyActor(this);
	//}

	/// Disable all collision on capsule.
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	//DetachFromControllerPendingDestroy();
	PlayDeathAnimation();
}

void ABaseCharacter::PlayDeathAnimation()
{
	bool IsDying = false;

	if (IsPendingKill())
	{
		IsDying = false;
	}
	else
	{
		/// Crumble mesh.
		UDestructibleComponent* DestructibleMesh = (UDestructibleComponent*)GetComponentByClass(UDestructibleComponent::StaticClass());
		DestructibleMesh->ApplyDamage(10.0f, GetActorLocation(), FVector(0, 0, -1), 10.0f);
		IsDying = true;
	}

	if (!IsDying)
	{
		/// Hide the character immediately.
		TurnOff();
		SetActorHiddenInGame(true);
		SetLifeSpan(1.0f);
	}
	else
	{
		SetLifeSpan(5.0f);
	}
}