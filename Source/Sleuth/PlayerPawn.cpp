// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "PlayerPawn.h"
#include "PlayerPawnMovementComponent.h"


// Sets default values.
APlayerPawn::APlayerPawn() : CameraHeight(1000.0f),
							 CameraRotation(FRotator(-90.0f, 0.0f, 0.0f)),
							 CameraLagSpeed(3.0f),
							 SphereRadius(50.0f)
{
 	/// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// Root component that reacts to physics.
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(SphereRadius);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	/// Create and poisition the actor's mesh component for visual aid in the scene.
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	SphereMesh->SetupAttachment(RootComponent);

	/// Setup the partile system for stealth.
	StealthParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("StealthParticles"));
	StealthParticleSystem->SetupAttachment(RootComponent);
	StealthParticleSystem->bAutoActivate = false;

	/// Spring arm for the camera.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = CameraRotation;
	SpringArm->TargetArmLength = CameraHeight;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = CameraLagSpeed;

	/// Setup the camera with the spring arm.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	/// Create an instance of the pawn movement component and tell it to update the root.
	MovementComponent = CreateDefaultSubobject<UPlayerPawnMovementComponent>(TEXT("CustomMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	/// Take control of the default player.
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned.
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	/// Apply changes made in the editor.
	SpringArm->TargetArmLength = CameraHeight;
}

// Called every frame.
void APlayerPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input.
void APlayerPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &APlayerPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);
}

// Returns custom pawn movement component.
UPawnMovementComponent* APlayerPawn::GetMovementComponent() const
{
	return MovementComponent;
}

void APlayerPawn::MoveForward(float AxisValue)
{
	if (MovementComponent && MovementComponent->UpdatedComponent == RootComponent)
	{
		MovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void APlayerPawn::MoveRight(float AxisValue)
{
	if (MovementComponent && MovementComponent->UpdatedComponent == RootComponent)
	{
		MovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}