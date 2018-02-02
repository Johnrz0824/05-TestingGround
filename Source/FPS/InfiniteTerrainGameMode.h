// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
class ANavMeshBoundsVolume;
class UActorPool;
UCLASS()
class FPS_API AInfiniteTerrainGameMode : public AFPSGameMode
{
	GENERATED_BODY()
	
public:
	AInfiniteTerrainGameMode();

public:
	UFUNCTION(BlueprintCallable, Category="Pool")
	void PopulateBoundsVolumePool();
	
private:
	void AddToPool(ANavMeshBoundsVolume *VolumeToAdd);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	UActorPool* NavMeshBoundPool;

};
