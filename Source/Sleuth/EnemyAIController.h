// Copyright Adam Joyce 2017.

#pragma once

#include "AIController.h"
#include "EnemyAIController.generated.h"


UCLASS()
class SLEUTH_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

private:
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

	/* Pushes the target enemy to the blackboard. */
	void SetTargetEnemy(APawn* NewTarget);
};
