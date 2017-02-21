// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter() : Health(100.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float ABaseCharacter::GetHealth() const
{
	return Health;
}

