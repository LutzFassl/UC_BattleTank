// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/SceneComponent.h"
//#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT(" %s firing at %s"), *GetOwner()->GetName(), *AimDirection.ToString()); 
		MoveBarrelTowards(AimDirection);


	}
	


	//auto BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT(" %s aiming from %s at %s"), *GetOwner()->GetName(), *BarrelLocation.ToString(),*HitLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT(" %s firing at %f"), *GetOwner()->GetName(),LaunchSpeed);
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	// Work out difference between barrel direction and aim direction
	// Transform Difference into Roll,Pitch,Yaw for the Turret
	// Check if it has a solution
	// Move barrel right amount this frame, max elev speed and frame time
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

