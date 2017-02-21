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
	float GetHealth() const;

protected:
	/* The character's health pool - zero means game over. */
	UPROPERTY(EditDefaultsOnly, Category = "PlayerCondition")
	float Health;
};
