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
	if (GetSightRayHitLocation(HitLocation));

	//if (GetSightRayHitLocation()) { UE_LOG(LogTemp, Warning, TEXT("I'm hitting something")); } // TEST Ticking; }

	UE_LOG(LogTemp, Warning, TEXT("Vector HitLocation: %s"), *HitLocation.ToString()); // TEST Ticking

	// Get world location of linetrace through crosshair
	// If it hits the landscape
		// tell controlled tank to to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	
	
	// Out the FVector Hitlocation
	FVector PlayerViewPointLocation = FVector(5000.f, 100.f,1000.f);
	FRotator PlayerViewPointRotation;
	FVector endvector = FVector(100000.f, 100.f, 1000.f);
	
	FHitResult HitResult;

	GetOwner()->GetActorEyesViewPoint(
		OUT PlayerViewPointLocation,		// OUT does nothing (see include above), just to highlight where input parameters are changed
		OUT PlayerViewPointRotation
	);

	endvector = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * 100; //+ FVector(0.f, 0.f, Reach);

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, endvector, FColor(255, 0, 255), false, 0.f, 0.f, 20.f);
	
	bool DidWork = GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		PlayerViewPointLocation,
		endvector,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),	// TODO aim for world or tanks, like physics bodies?
		TraceParameters);

	AActor* ActorHit = HitResult.GetActor();
	//UE_LOG(LogTemp, Warning, TEXT("We hit the: %s"), *ActorHit->GetName()); // TEST Ticking
	if (ActorHit)
	{
	HitLocation = HitResult.Location;
	UE_LOG(LogTemp, Warning, TEXT("We hit the %s at: %s"), *ActorHit->GetName(), *HitLocation.ToString()); // TEST Ticking
	}

	return DidWork;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


