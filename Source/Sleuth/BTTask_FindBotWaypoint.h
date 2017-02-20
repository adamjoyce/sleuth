// Copyright Adam Joyce 2017.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindBotWaypoint.generated.h"


UCLASS()
class SLEUTH_API UBTTask_FindBotWaypoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};
