// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "BTTask_FindPatrolLocation.h"
#include "BotWaypoint.h"
#include "EnemyAIController.h"

/* AI Modules. */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* Contains all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


EBTNodeResult::Type UBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComponent.GetAIOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	ABotWaypoint* CurrentWaypoint = AIController->GetWaypoint();
	if (CurrentWaypoint)
	{
		/// Find a position close to the current waypoint.
		/// A small random is added to the position to build predictable patrol patterns.
		const float SearchRadius = 200.0f;
		const FVector SearchOrigin = CurrentWaypoint->GetActorLocation();
		const FVector Location = UNavigationSystem::GetRandomPointInNavigableRadius(AIController, SearchOrigin, SearchRadius);
		if (Location != FVector::ZeroVector)
		{
			/// The selected key should be "PatrolLocation" in the BehaviorTree setup.
			OwnerComponent.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), Location);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
