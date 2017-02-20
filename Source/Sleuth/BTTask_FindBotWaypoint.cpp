// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "BTTask_FindBotWaypoint.h"
#include "BotWaypoint.h"
#include "EnemyAIController.h"

/* AI Modules. */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* Contains all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


EBTNodeResult::Type UBTTask_FindBotWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComponent.GetAIOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	ABotWaypoint* CurrentWaypoint = AIController->GetWaypoint();
	AActor* NewWaypoint = nullptr;

	/// Iterate all the bot waypoints in the current level and find a new random waypoint.
	TArray<AActor*> AllWaypoints;
	UGameplayStatics::GetAllActorsOfClass(AIController, ABotWaypoint::StaticClass(), AllWaypoints);

	if (AllWaypoints.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	/// Find a new waypoint ranomly by index (including current waypoint).
	/// EXPAND WITH MORE COMPLEX LOGIC i.e. WEIGHTINGS.
	NewWaypoint = AllWaypoints[FMath::RandRange(0, AllWaypoints.Num() - 1)];

	/// Assign the new waypoint to the blackboard.
	if (NewWaypoint)
	{
		AIController->SetWaypoint(Cast<ABotWaypoint>(NewWaypoint));
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
