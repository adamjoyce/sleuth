// Copyright Adam Joyce 2017.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class SLEUTH_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/* Sets default values for this character's properties. */
	AEnemyCharacter();

	/* The brain of the enemy - makes decisions based on data from the blackboard. */
	/* Assigned at the character level to enable reuse of the enemy AI controller. */
	UPROPERTY(EditDefaultsOnly, Category="AI")
	class UBehaviorTree* BehaviorTree;

	/* Called when the game starts or when spawned. */
	virtual void BeginPlay() override;
	
	/* Called every frame. */
	virtual void Tick( float DeltaSeconds ) override;

protected:
	/* Triggered by the pawn sensing component when a pawn is spotted. */
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

private:
	/* Last time the player was spotted. */
	float LastSeenTime;

	/* Handles the enemy's senses. */
	UPROPERTY(VisibleAnywhere, Category="AI")
	class UPawnSensingComponent* PawnSensingComponent;
};
