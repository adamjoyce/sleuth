// Copyright Adam Joyce 2017.

#pragma once

#include "AIController.h"
#include "EnemyAIController.generated.h"


UCLASS()
class SLEUTH_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

private:
	/* Blackboard key name for the target player pawn. */
	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName TargetEnemyKeyName;

	/* Blackboard key name for the target location. */
	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName TargetLocationKeyName;

	/* Blackboard key name for the target location. */
	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName HomeLocationKeyName;

	/* The behaviour tree component. */
	UBehaviorTreeComponent* BehaviorComponent;

	/* The behaviour tree's blackboard. */
	UBlackboardComponent* BlackboardComponent;

	/* Called whenever the controller possesses a character bot. */
	virtual void Possess(class APawn* InPawn) override;

	/* Called when the AI controller loses control of the character bot. */
	virtual void UnPossess() override;

public:
	AEnemyAIController();

	/* Returns the target enemy stored in the blackboard. */
	APawn* GetTargetEnemy();

	/* Pushes the target enemy to the blackboard. */
	void SetTargetEnemy(APawn* NewTarget);

	/* Pushes the target location to the blackboard. */
	void SetTargetLocation();

	/* Puches the home location to the blackboard. */
	void SetHomeLocation(APawn* TargetPawn);
};
