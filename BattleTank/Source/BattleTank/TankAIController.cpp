// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

//#include "Engine/World.h"		kann man einkommentieren wenn es st�rt, dass VB GetWorld nicht kennt

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	//if (!Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn())) { return; } // get out if no player is found possessed
	if (ensure(PlayerTank))
	{	
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);	
		
		FVector HitLocation = PlayerTank->GetActorLocation();
		ControlledTank->AimAt(HitLocation);
		ControlledTank->Fire();
	 }
	
	return;
}

