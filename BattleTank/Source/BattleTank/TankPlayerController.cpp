// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
//#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"




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

	//if (GetSightRayHitLocation()) { UE_LOG(LogTemp, Warning, TEXT("I'm hitting something")); } // TEST Ticking; }

	

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
	GetLookDirection(ScreenLocation, LookDirection);

	//// Ray-Casting
	//FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//FHitResult HitResult;
	//bool DidWork = GetWorld()->LineTraceSingleByObjectType(
	//	HitResult,
	//	CameraWorldLocation,
	//	CameraWorldDirection * 100000,
	//	FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
	//	TraceParameters);

	//// See what we hit
	//AActor* ActorHit = HitResult.GetActor();
	//if (ActorHit)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("We hit the: %s"), *ActorHit->GetName()); // TEST Ticking
	//	//UE_LOG(LogTemp, Warning, TEXT("We hit the %s at: %s"), *ActorHit->GetName(), *HitLocation.ToString()); // TEST Ticking
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("We hit nothing")); // TEST Ticking
	//}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	// Project from camera through crosshair
	FVector CameraWorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection)) { return true; }

	return false;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


