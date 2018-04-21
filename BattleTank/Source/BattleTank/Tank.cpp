// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	//LastFireTime = FPlatformTime::Seconds();
}

//void ATank::Fire()
//{
//	if (!ensure(Barrel)) { return; }
//	bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds;
//	
//	if (isReloaded)
//	{
//		// spawn projectile at socket location
//		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
//		FRotator StartRotation = Barrel->GetSocketRotation(FName("Projectile"));
//		//UE_LOG(LogTemp, Warning, TEXT("Projectile Rot: %s"), *StartRotation.ToString());
//
//		// spawn and fire projectile
//		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, StartLocation, StartRotation);
//		Projectile->LaunchProjectile(LaunchSpeed);
//		LastFireTime = FPlatformTime::Seconds();	// Set Time of last fire event
//	}
//}


