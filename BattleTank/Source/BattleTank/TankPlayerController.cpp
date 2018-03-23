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

	//UE_LOG(LogTemp, Warning, TEXT("PlayerController is ticking")); // TEST Ticking

	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	// TODO Code
	if(!GetControlledTank())	{	return;	} // get out if no tank

	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Vector HitLocation: %s"), *HitLocation.ToString()); // TEST Ticking
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
	FVector CameraWorldLocation;
	if (GetLookDirection(ScreenLocation, CameraWorldLocation, LookDirection))
	{
		//// Ray-Casting / Line Tracing
		GetLookVectorHitLocation(CameraWorldLocation, LookDirection);
	}

	return true;
}

// Calculate 3D Look direction from 2D Crosshair position. Use OUT Parameter LookDirection
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &CameraWorldLocation, FVector & LookDirection) const
{
	
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection)) { return true; }
	

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &Location, FVector & LookDirection) const	//needs position and direction
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FCollisionResponseParams ResponseParam(ECollisionResponse::ECR_Overlap);

	DrawDebugLine(GetWorld(), Location + LookDirection.GetSafeNormal() * 2000, LookDirection.GetSafeNormal() * 1000000, FColor(255, 0, 255), false, 0.f, 0.f, 25.f);


	FHitResult HitResult;
	bool DidWork = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Location,
		LookDirection.GetSafeNormal() * 1000000,		// Normalized to 1 unit = 1cm; multiplied with 1'000'000 to set length to 10km
		ECollisionChannel::ECC_Visibility,
		TraceParameters,
		ResponseParam);

	// See what we hit
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("We hit the: %s"), *ActorHit->GetName()); // TEST Ticking
		//UE_LOG(LogTemp, Warning, TEXT("We hit the %s at: %s"), *ActorHit->GetName(), *HitLocation.ToString()); // TEST Ticking
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("We hit nothing")); // TEST Ticking
	}
	
	return DidWork;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


