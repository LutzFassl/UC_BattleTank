// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
//#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
//#include "Math/Vector.h"




ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetControlledTank())
	{
		FString MyPawn = GetControlledTank()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("I'm the player. My name is %s"), *MyPawn);
	}
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	
	if(!GetControlledTank())	{	return;	} // get out if no tank

	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

	

	

	// Get world location of linetrace through crosshair
	// If it hits the landscape
		// tell controlled tank to to aim at this point
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

	return true;
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
	//FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());	//Definition of optional parameters not necessary
	//FCollisionResponseParams ResponseParam(ECollisionResponse::ECR_Overlap);		//Definition of optional parameters not necessary

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;	// No Normalization necessary, already Unit vector; 1 unit = 1cm; multiplied with 1'000'000 to set length to 10km


	//DrawDebugLine(GetWorld(), StartLocation + LookDirection * 2000, EndLocation, FColor(255, 0, 255), false, 0.f, 0.f, 25.f);

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(		// Channel because it doesn't matter WHAT we're hitting, only WHERE we hit
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
		//TraceParameters,		--> not necessary OPTIONAL
		//ResponseParam			--> not necessary OPTIONAL
	)) 
	{
		HitLocation =	HitResult.Location;
		return true;
	}
	
	return false;
	HitLocation = FVector(0);
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


