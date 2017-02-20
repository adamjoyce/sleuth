// Copyright Adam Joyce 2017.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SLEUTH_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties.
	AEnemyActor();

	// Visual mesh component.
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	// Visual mesh component.
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisionCone;

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;
	
	// Called every frame.
	virtual void Tick( float DeltaSeconds ) override;

private:
	// The actor's movement speed.
	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed;

	/* --- MAKE CONSTANT ONCE HAPPY WITH VALUES --- */
	// The radius of the sphere used to determine a new wander target vector.
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float WanderTargetRadius;

	// The distance the wander target sphere is projected infront of the actor.
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float WanderTargetDistance;

	// Jitter for the wander target vector.
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float WanderTargetJitter;
	/* --- MAKE CONSTANT ONCE HAPPY WITH VALUES --- */

	// Random direction vector deviation.
	FVector WanderTarget;

	// Root component that reacts to physics.
	UBoxComponent* BoxComponent;

	// Generates a random binomial between -1.0f and 1.0f with a imbalance towards 0.0f.
	const float RandomBinomial();
};
