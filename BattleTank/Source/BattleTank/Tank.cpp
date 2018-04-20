// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers because it's added at construction
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds;
	
	if (isReloaded)
	{
		// spawn projectile at socket location
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator StartRotation = Barrel->GetSocketRotation(FName("Projectile"));
		//UE_LOG(LogTemp, Warning, TEXT("Projectile Rot: %s"), *StartRotation.ToString());

		// spawn and fire projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, StartLocation, StartRotation);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();	// Set Time of last fire event
	}
}

FString ATank::GetRemainingReload()
{
	float rawReloadLeft = ReloadTimeInSeconds - (FPlatformTime::Seconds() - LastFireTime);
	if (rawReloadLeft <= 0)
	{
		return "Reloaded";
	}
	else
	{
		float RoundedValue = FMath::RoundHalfFromZero(rawReloadLeft * 100) / 100;
		return FString::SanitizeFloat(RoundedValue);
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	
}

