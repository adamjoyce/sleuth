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

	// Random direction vector deviation.
	FVector WanderTarget;

	// Root component that reacts to physics.
	UBoxComponent* BoxComponent;

	// Generates a random binomial between -1.0f and 1.0f with a imbalance towards 0.0f.
	const float RandomBinomial();
};
