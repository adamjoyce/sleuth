// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "Types.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


AEnemyAIController::AEnemyAIController() : TargetEnemyKeyName("TargetEnemy"),
										   TargetLocationKeyName("TargetLocation"),
										   HomeLocationKeyName("HomeLocation"),
										   BotTypeKeyName("BotType"),
										   CurrentWaypointKeyName("CurrentWaypoint")
{
	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AEnemyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AEnemyCharacter* EnemyBot = Cast<AEnemyCharacter>(InPawn);
	if (EnemyBot)
	{
		if (EnemyBot->BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*EnemyBot->BehaviorTree->BlackboardAsset);

			/// Make sure blackboard has the type of the bot we possessed.
			SetBlackboardBotType(EnemyBot->BotType);
		}

		BehaviorComponent->StartTree(*EnemyBot->BehaviorTree);
	}
}

void AEnemyAIController::UnPossess()
{
	Super::UnPossess();

	/// Stop any behavior running as we no longer have a pawn to control.
	BehaviorComponent->StopTree();
}

APawn* AEnemyAIController::GetTargetEnemy()
{
	if (BlackboardComponent)
	{
		return Cast<APawn>(BlackboardComponent->GetValueAsObject(TargetEnemyKeyName));
	}

	return nullptr;
}

ABotWaypoint* AEnemyAIController::GetWaypoint()
{
	if (BlackboardComponent)
	{
		return Cast<ABotWaypoint>(BlackboardComponent->GetValueAsObject(CurrentWaypointKeyName));
	}

	return nullptr;
}

void AEnemyAIController::SetTargetEnemy(APawn* NewTarget)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsObject(TargetEnemyKeyName, NewTarget);
	}
}

void AEnemyAIController::SetWaypoint(ABotWaypoint* NewWaypoint)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsObject(CurrentWaypointKeyName, NewWaypoint);
	}
}

void AEnemyAIController::SetTargetLocation()
{
	if (BlackboardComponent)
	{
		APawn* TargetEnemy = GetTargetEnemy();
		if (TargetEnemy)
		{
			BlackboardComponent->SetValueAsVector(TargetLocationKeyName, TargetEnemy->GetActorLocation());
		}
	}
}

void AEnemyAIController::SetHomeLocation(APawn* TargetPawn)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsVector(HomeLocationKeyName, TargetPawn->GetActorLocation());
	}
}

void AEnemyAIController::SetBlackboardBotType(EBotBehaviorType NewType)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsEnum(BotTypeKeyName, (uint8)(NewType));
	}
}
