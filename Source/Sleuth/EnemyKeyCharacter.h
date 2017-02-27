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

    ///* Called when the game starts or when spawned. */
    //virtual void BeginPlay() override;

    ///* Called every frame. */
    //virtual void Tick(float DeltaSeconds) override;

public:
    AEnemyKeyCharacter();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LockedDoor")
    class ALockedDoor* LockedDoor;
};
