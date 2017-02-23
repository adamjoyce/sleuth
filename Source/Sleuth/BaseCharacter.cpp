// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter() : Health(100.0f)
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
			/// Temporary player respawn.
			if (GetWorld())
			{
                GetWorld()->DestroyActor(this);
				UGameplayStatics::GetGameMode(GetWorld())->RestartPlayer(GetWorld()->GetFirstPlayerController());
                UE_LOG(LogTemp, Warning, TEXT("RESPAWN"));
			}
		}
	}

	return DamageToTake;
}

