// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter() : MovementSpeed(2000.0f),
									   CameraHeight(2000.0f),
									   CameraRotation(FRotator(-90.0f, 0.0f, 0.0f)),
									   CameraLagSpeed(3.0f)
{
 	/// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// Create the character's visible mesh.
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));
	SphereMesh->SetupAttachment(RootComponent);
	SphereMesh->SetCollisionProfileName("NoCollision");

	/// Spring arm for the camera.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = CameraRotation;
	SpringArm->TargetArmLength = CameraHeight;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = CameraLagSpeed;
	SpringArm->bDoCollisionTest = false;

	/// Setup the camera with the spring arm.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;

	///// Take control of the default player.
	//AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned.
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/// Apply changes that may have been made in the editor.
	SpringArm->TargetArmLength = CameraHeight;
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

// Called every frame.
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input.
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}
