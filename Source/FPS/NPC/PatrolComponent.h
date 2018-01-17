// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FPS_API UPatrolComponent : public UActorComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
		TArray<AActor*> PatrolPointsCPP;

public:
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetPatrolPoints();
	
};
