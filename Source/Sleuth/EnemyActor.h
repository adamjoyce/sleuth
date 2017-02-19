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

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;
	
	// Called every frame.
	virtual void Tick( float DeltaSeconds ) override;

private:
	// Root component that reacts to physics.
	UBoxComponent* BoxComponent;
};
