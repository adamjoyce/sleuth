// Copyright Adam Joyce 2017.

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"


UCLASS()
class SLEUTH_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties.
	APlayerPawn();

	// Height of the player camera.
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float CameraHeight;

	// Visual mesh for pawn.
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SphereMesh;

	// Stealth particle system.
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* StealthParticleSystem;

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;
	
	// Called every frame.
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input.
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Returns custom pawn movement component.
	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	// Camera rotation attached to spring arm.
	FRotator CameraRotation;

	// Lag speed of the camera acttahed to the spring arm.
	float CameraLagSpeed;

	// Sphere radius size.
	float SphereRadius;

	// Sphere component for the pawn.
	USphereComponent* SphereComponent;

	// Player camera.
	UCameraComponent* Camera;

	// Spring arm for smooth camera transistions.
	USpringArmComponent* SpringArm;

	// Player movement component.
	class UPlayerPawnMovementComponent* MovementComponent;

	// Moves the pawn along its forward vector.
	void MoveForward(float AxisValue);

	// Moves the pawn along its right vector.
	void MoveRight(float AxisValue);
};
