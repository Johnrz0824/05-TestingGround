// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int count = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < count; i++)
	{
		float sizeScale = FMath::RandRange(MinScale, MaxScale);
		FVector spawnPoint;
		if (FindEmptyLocation(spawnPoint, Radius, sizeScale,5))
		{
			float randomRotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, spawnPoint, randomRotation, sizeScale);
		}
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
	FVector min(0, -2000, 0);
	FVector max(4000, 2000, 0);
	FBox bounds(min, max);
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

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale)
{
	auto actor =GetWorld()->SpawnActor<AActor>(ToSpawn);
	actor->SetActorRelativeLocation(SpawnPoint);
	actor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	actor->SetActorRotation(FRotator(0, Rotation, 0));
	actor->SetActorScale3D(FVector(Scale));
}