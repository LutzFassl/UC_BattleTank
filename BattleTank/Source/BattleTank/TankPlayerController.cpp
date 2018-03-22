// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"




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
	if(!GetControlledTank)	{		return;	} // get out if no tank

	// Get world location of linetrace through crosshair
	// If it hits the landscape
		// tell controlled tank to to aim at this point
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


