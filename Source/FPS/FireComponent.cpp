// Fill out your copyright notice in the Description page of Project Settings.

#include "FireComponent.h"
#include "Engine/World.h"
#include "FPSProjectile.h"


// Sets default values for this component's properties
UFireComponent::UFireComponent()
{
}

void UFireComponent::Fire()
{
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetComponentRotation();
			const FVector SpawnLocation = GetComponentLocation();
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}