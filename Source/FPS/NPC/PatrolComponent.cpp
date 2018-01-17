// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolComponent.h"


TArray<AActor*> UPatrolComponent::GetPatrolPoints()
{
	return PatrolPointsCPP;
}

