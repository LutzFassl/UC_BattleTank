// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/SceneComponent.h"
//#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"




// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("DONKEY::TankAimingComponent.cpp Constructor"));
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel){return;}

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
		//Log reporting function
		//if (bLastSolution == false) {
		//	bLastSolution = true;
		//	auto OwningTank = GetOwner()->GetName();
		//	UE_LOG(LogTemp, Warning, TEXT("%f: Aiming solution found by %s"), Time, *OwningTank);
		//}

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
	else
	{
		// no Aiming solution found

		// complain that no solution was found to log but only once

		//Log reporting function
		//if (bLastSolution == true) 
		//{
		//bLastSolution = false;
		//auto OwningTank = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aiming solution lost by %s"), Time, *OwningTank);
		//}
		
	}	
}

void UTankAimingComponent::AimingInitialize(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	if (!TurretToSet || !BarrelToSet) { return; }
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Turret || !Barrel) { return; }
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
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);		
	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotator.Yaw: %f"), DeltaRotator.Yaw);
}