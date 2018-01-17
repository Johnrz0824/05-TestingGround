// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolComponent.h"


EBTNodeResult::Type UChooseWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrolComponent = ControlledPawn->FindComponentByClass<UPatrolComponent>();
	if(!ensure(PatrolComponent)) { return EBTNodeResult::Failed; }
	auto PatrolPoints = PatrolComponent->GetPatrolPoints();

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	index = (index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, index);
	auto Target = PatrolPoints[index];
	if (!Target) { return EBTNodeResult::Failed; }

	BlackboardComp->SetValueAsObject(WayPointKey.SelectedKeyName, Target);
	return EBTNodeResult::Succeeded;

}
