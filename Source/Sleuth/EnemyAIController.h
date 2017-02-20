// Copyright Adam Joyce 2017.

#pragma once

/* Included to avoid Engine bug involving using ENUMs with UPROPERTY. */
#include "Types.h"

#include "AIController.h"
#include "BotWaypoint.h"
#include "EnemyAIController.generated.h"


UCLASS()
class SLEUTH_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	/* Blackboard key name for the target player pawn. */
	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName TargetEnemyKeyName;

	/* Blackboard key name for the target location. */
	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName TargetLocationKeyName;

	/* Blackboard key name for the target location. */
	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName HomeLocationKeyName;

	/* Blackboard key name for the target location. */
	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName BotTypeKeyName;

	/* Blackboard key name for the current waypoint. */
	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName CurrentWaypointKeyName;

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

	/* Returns the current waypoint stored in the blackboard. */
	ABotWaypoint* GetWaypoint();

	/* Pushes the target enemy to the blackboard. */
	void SetTargetEnemy(APawn* NewTarget);

	/* Pushes the current waypoint to the blackboard. */
	void SetWaypoint(ABotWaypoint* NewWaypoint);

	/* Pushes the target location to the blackboard. */
	void SetTargetLocation();

	/* Puches the home location to the blackboard. */
	void SetHomeLocation(APawn* TargetPawn);

	void SetBlackboardBotType(EBotBehaviorType NewType);
};
