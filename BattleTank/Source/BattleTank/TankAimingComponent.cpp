// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	//Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	
	if (FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{ 
		FiringState = EFiringState::Reloading;
	}
	
	//My appraoch - to delete
	//float rawReloadLeft = ReloadTimeInSeconds - (FPlatformTime::Seconds() - LastFireTime);
	//if (rawReloadLeft > 0) { FiringState = EFiringState::Reloading; }
	//if (DeltaRotator1.Pitch < 1 && DeltaRotator2.Yaw < 1 && rawReloadLeft <= 0) { FiringState = EFiringState::Locked; }
	//if (DeltaRotator1.Pitch > 1 && DeltaRotator2.Yaw > 1 && rawReloadLeft <= 0) { FiringState = EFiringState::Aiming; }
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f"), DeltaRotator1.Pitch, DeltaRotator2.Yaw);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)){return;}

	//UObject * WorldContextObject;
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector EndLocation = HitLocation;

	// Calculate the OutLaunchVelocity
	TArray < AActor * > ActorsToIgnore;
	FCollisionResponseParams ResponseParam;

	bool bHaveAimSolution;
	bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			EndLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
  // true for debuglines
		);

	auto Time = GetWorld()->GetTimeSeconds();
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
	else
	{
		// no Aiming solution found
	}	
}

void UTankAimingComponent::AimingInitialize(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	if (!ensure(TurretToSet && BarrelToSet)) { return; }
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure (Turret && Barrel)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	// Work out difference between barrel direction and aim direction
	// Transform Difference into Roll,Pitch,Yaw for the Turret
	// Check if it has a solution
	// Move barrel right amount this frame, max elev speed and frame time
	
	Barrel->Elevate(DeltaRotator.Pitch);		
	
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(Turret)) { return; }
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);		
	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotator.Yaw: %f"), DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(ProjectileBlueprint && Barrel)) { return; }
	if (FiringState != EFiringState::Reloading)
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

FString UTankAimingComponent::GetRemainingReload()
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