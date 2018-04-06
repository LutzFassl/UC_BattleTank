// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

//#include "Engine/World.h"		kann man einkommentieren wenn es stört, dass VB GetWorld nicht kennt

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	//if (PlayerTank) { return; } // get out if no tank possessed
	//if (!Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn())) { return; } // get out if no player is found possessed
	if (PlayerTank)
	{	
		FVector HitLocation = PlayerTank->GetActorLocation();
		ControlledTank->AimAt(HitLocation);
		ControlledTank->Fire(); // TODO dont fire every frame
	 }
	
	return;
}

