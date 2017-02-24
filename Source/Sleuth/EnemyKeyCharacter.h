// Copyright Adam Joyce 2017.

#pragma once

#include "EnemyCharacter.h"
#include "EnemyKeyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SLEUTH_API AEnemyKeyCharacter : public AEnemyCharacter
{
    GENERATED_BODY()

public:
    AEnemyKeyCharacter();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LockedDoor")
    class ALockedDoor* LockedDoor;
};
