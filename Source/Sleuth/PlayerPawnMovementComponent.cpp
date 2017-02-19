// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "PlayerPawnMovementComponent.h"

UPlayerPawnMovementComponent::UPlayerPawnMovementComponent() : PawnSpeed(1000.0f) {}

// Called when the game starts or when spawned.
void UPlayerPawnMovementComponent::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame.
void UPlayerPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Ensure we are still allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	/// Get (and then clear) the movement vector.
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * PawnSpeed;
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		/// If we bumped into something, try and slide along it.
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}