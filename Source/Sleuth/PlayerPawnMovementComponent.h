// Copyright Adam Joyce 2017.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "PlayerPawnMovementComponent.generated.h"


UCLASS()
class SLEUTH_API UPlayerPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UPlayerPawnMovementComponent();

	// The speed the pawn moves.
	UPROPERTY(EditAnywhere, Category="Movement")
	float PawnSpeed;

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Called every frame.
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
