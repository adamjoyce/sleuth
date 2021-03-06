// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter() : MovementSpeed(2000.0f),
									   CameraHeight(2000.0f),
									   CameraRotation(FRotator(-60.0f, 0.0f, 0.0f)),
									   CameraLagSpeed(3.0f),
									   BackstabCharacter(nullptr)
{
 	/// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// Create the character's visible mesh.
	//SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));
	//SphereMesh->SetupAttachment(RootComponent);
	//SphereMesh->SetCollisionProfileName("NoCollision");

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

	InputComponent->BindAction("Backstab", IE_Pressed, this, &APlayerCharacter::Backstab);

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

void APlayerCharacter::Backstab()
{
	if (BackstabCharacter != nullptr && IsAlive())
	{
		ACharacter* EnemyCharacter = Cast<ACharacter>(BackstabCharacter);

		/// Kill the enemy.
		FDamageEvent DamageEvent;
		EnemyCharacter->TakeDamage(BackstabCharacter->GetHealth(), DamageEvent, GetController(), this);

		UE_LOG(LogTemp, Warning, TEXT("BACKSTAB 'EM"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOTHING"));
	}
}

ABaseCharacter* APlayerCharacter::GetBackstabCharacter()
{
	return BackstabCharacter;
}

void APlayerCharacter::SetBackstabCharacter(ABaseCharacter* _BackstabCharacter)
{
	if (_BackstabCharacter)
	{
		BackstabCharacter = _BackstabCharacter;
	}
	else
	{
		BackstabCharacter = nullptr;
	}
}

void APlayerCharacter::OnDeath()
{
	Super::OnDeath();

	/// Resets the player.
	//if (GetWorld())
	//{
	//	UGameplayStatics::GetGameMode(GetWorld())->RestartPlayer(GetWorld()->GetFirstPlayerController());
	//}
}

void APlayerCharacter::LifeSpanExpired()
{
	Super::LifeSpanExpired();

	/// Resets the player.
	if (GetWorld())
	{
		UGameplayStatics::GetGameMode(GetWorld())->RestartPlayer(GetWorld()->GetFirstPlayerController());
	}
}
