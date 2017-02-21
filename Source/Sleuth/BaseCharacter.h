// Copyright Adam Joyce 2017.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class SLEUTH_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/* Sets default values for this character's properties. */
	ABaseCharacter();

	/* Returns the player's current health. */
	UFUNCTION()
	float GetHealth() const;

	/* Is the character above zero health? */
	UFUNCTION()
	bool IsAlive() const;

protected:
	/* The character's health pool - zero means game over. */
	UPROPERTY(EditAnywhere, Category = "PlayerCondition")
	float Health;

	/* Damage. */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
};
