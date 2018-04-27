// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
//#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TankAimingComponent.h"
//#include "Math/Vector.h"



ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GetPawn())) { return; }

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController can't find AimingComponent at BeginPlay"));
	}
		
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn())) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(!ensure(AimingComponent))	{	return;	} // get out if no tank

	FVector HitLocation; // Out Parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("GotHitLocation: %s"), (bGotHitLocation ? TEXT("True") : TEXT("False")));
	//UE_LOG(LogTemp, Warning, TEXT("GotHitLocation: %i"), bGotHitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Hitlocation: %s"), *HitLocation.ToString());

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	
	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;	// OUT parameters
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	// Deproject = Calculate 3D Location from Crosshair
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Ray-Casting / Line Tracing
		GetLookVectorHitLocation(LookDirection,HitLocation);
	}

	return !HitLocation.Equals(FVector(0), 0.01);
}

// Calculate 3D Look direction from 2D Crosshair position. Use OUT Parameter LookDirection
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const	// TODO really need cameraworldlocation?
{
	FVector CameraWorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection)) { return true; }
	
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const	//needs position and direction
{
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;	// No Normalization necessary, already Unit vector; 1 unit = 1cm; multiplied with 1'000'000 to set length to 10km

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(		// Channel because it doesn't matter WHAT we're hitting, only WHERE we hit
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	)) 
	{
		HitLocation =	HitResult.Location;
		return true;
	}
	
	return false;
	HitLocation = FVector(0);
}

