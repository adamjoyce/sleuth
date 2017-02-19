// Copyright Adam Joyce 2017.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "PlayerPawnMovementComponent.generated.h"


UCLASS()
class SLEUTH_API UPlayerPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	// Called every frame.
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
