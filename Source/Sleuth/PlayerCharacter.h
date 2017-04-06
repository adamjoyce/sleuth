// Copyright Adam Joyce 2017.

#pragma once

#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SLEUTH_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	/* Sets default values for this character's properties. */
	APlayerCharacter();

	/* Returns the current backstabable character. */
	ABaseCharacter* GetBackstabCharacter();

	/* Sets a new backstabable character. */
	void SetBackstabCharacter(ABaseCharacter* _BackstabCharacter);

protected:
	/* What the character does on death. */
	virtual void OnDeath() override;

	/* Used for restarting the player character once it's life span ends. */
	virtual void LifeSpanExpired() override;

private:
	/* Height of the player camera. */
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float CameraHeight;

	/* Speed the character travels at. */
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MovementSpeed;

	/* Camera rotation attached to spring arm. */
	FRotator CameraRotation;

	/* Lag speed of the camera acttahed to the spring arm. */
	float CameraLagSpeed;

	/* Backstabable character that is within range. */
	ABaseCharacter* BackstabCharacter;

	/* Sphere component for the pawn. */
	USphereComponent* SphereComponent;

	/* Player camera. */
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	/* Spring arm for smooth camera transistions. */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	/* Visual mesh for pawn. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SphereMesh;

	/* Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/* Called every frame. */
	virtual void Tick(float DeltaSeconds) override;

	/* Called to bind functionality to input. */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/* Moves the pawn along its forward vector. */
	void MoveForward(float AxisValue);

	/* Moves the pawn along its right vector. */
	void MoveRight(float AxisValue);

	/* Attempts to backstab an enemy. */
	void Backstab();
};
