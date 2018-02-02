// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;
UCLASS()
class FPS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();


	UFUNCTION(BlueprintCallable)
	void SetActorPool(UActorPool* PoolToSet);
	UFUNCTION(BlueprintCallable)
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 300, float MinScale = 1, float MaxScale = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndplayReason) override;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
		FVector NavigationBoundsOffset;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void PositionVavMeshBoundsVolume();
	bool CanSpawnAtLocation(FVector Location, float Radius, float Scale);
	bool FindEmptyLocation(FVector &OutLocation,float Radius, float Scale, int maxTry = 1);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale);
	UActorPool* ActorPool;
	AActor* NavMeshBoundsVolume;
};
