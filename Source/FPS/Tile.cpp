// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
	NavigationBoundsOffset = FVector(2000, 0, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndplayReason)
{
	ActorPool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int count = FMath::RandRange(MinSpawn, MaxSpawn);
	auto positions = CreateSpawnPositions(count, Radius,MinScale,MaxScale);
	for (auto& pos : positions)
	{
		PlaceActor(ToSpawn, pos);
	}
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius, float Scale)
{
	FHitResult hitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool hasHit = GetWorld()->SweepSingleByChannel(
		hitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	FColor resultColor = hasHit ? FColor::Red : FColor::Green;
	return hasHit;
}

bool ATile::FindEmptyLocation(FVector &OutLocation, float Radius, float Scale, int maxTry)
{
	FBox bounds(MinExtent, MaxExtent);
	for (int i = 0; i < maxTry; i++)
	{
		FVector point = FMath::RandPointInBox(bounds);
		if (!CanSpawnAtLocation(point, Radius, Scale))
		{
			OutLocation = point;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	auto actor =GetWorld()->SpawnActor<AActor>(ToSpawn);
	actor->SetActorRelativeLocation(SpawnPosition.Location);
	actor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	actor->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	actor->SetActorScale3D(FVector(SpawnPosition.Scale));
}

void ATile::SetActorPool(UActorPool* PoolToSet)
{
	ActorPool = PoolToSet;
	
	PositionVavMeshBoundsVolume();
}

void ATile::PositionVavMeshBoundsVolume()
{
	NavMeshBoundsVolume = ActorPool->Checkout();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Enough Actors in Pool"));
		return;
	}
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
}

TArray<FSpawnPosition> ATile::CreateSpawnPositions(int Nums, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPosition> arr;
	for (int i = 0; i < Nums; i++)
	{
		FSpawnPosition spawnPosition;
		spawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		if (FindEmptyLocation(spawnPosition.Location, Radius, spawnPosition.Scale, 5))
		{
			spawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			arr.Push(spawnPosition);
		}
	}
	return arr;
}