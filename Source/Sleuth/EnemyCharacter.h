// Copyright Adam Joyce 2017.

#pragma once

/* Included to avoid Engine bug involving using ENUMs with UPROPERTY. */
#include "Types.h"

#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class SLEUTH_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	/* Last time the player was spotted. */
	float LastSeenTime;

	/* Last time the enemy drained the player's health. */
	float LastHealthDrainTime;

	/* Resets after sense time-out to avoid unecessary clearing of target each tick. */
	bool bSensedTarget;

	/* Time-out value to clear the sensed position of the player. */
	/* Should be higher than sense interval in PawnSense to avoid missing sense ticks. */
	float SenseTimeOut;

	/* Health drain interval time. */
	float HealthDrainCooldown;

	/* Amount of damage drained each 'tick'. */
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float HealthDrainDamage;

	/* Handles the enemy's senses. */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComponent;

	/* Mesh for visbility in the scene. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisibleMesh;

	/* Mesh for sight cone in the scene. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SightMesh;

    /* Spot light to represent cone of vision. */
    UPROPERTY(VisibleAnywhere)
    USpotLightComponent* VisionCone;

	/* Materials for the sight cone. */
	UPROPERTY(EditDefaultsOnly, Category = "Materials")
	TArray<UMaterial*> Materials;

    /* Called when the game starts or when spawned. */
    virtual void BeginPlay() override;

    /* Called every frame. */
    virtual void Tick(float DeltaSeconds) override;

protected:
	/* Triggered by the pawn sensing component when a pawn is spotted. */
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

	/* Drains the pawn's health. */
	UFUNCTION()
	void PerformHealthDrain(AActor* HitActor);

public:
	/* Sets default values for this character's properties. */
	AEnemyCharacter();

	/* The brain of the enemy - makes decisions based on data from the blackboard. */
	/* Assigned at the character level to enable reuse of the enemy AI controller. */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	/* The bot behavior this bot will execute (passive/patrol). */
	UPROPERTY(EditAnywhere, Category="AI")
	EBotBehaviorType BotType;

	/* Change the default bot type during gameplay. */
	void SetBotType(EBotBehaviorType NewType);

    /* Returns if a player is currently detected. */
    UFUNCTION(BlueprintCallable, Category = "AI")
    bool IsTargetSensed();
};
