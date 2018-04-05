// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

//#include "Engine/World.h"		kann man einkommentieren wenn es stört, dass VB GetWorld nicht kennt

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank() && GetPlayerTank())
	{
		FString MyBot = GetControlledTank()->GetName();
		FString MyTarget = GetPlayerTank()->GetName();

		UE_LOG(LogTemp, Warning, TEXT("I'm a bot. My name is %s and I will hunt the player %s"), *MyBot, *MyTarget);
	}
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetControlledTank()) { return; } // get out if no tank possessed
	if (!GetPlayerTank()) { return; } // get out if no player is found possessed

	FVector HitLocation;
	HitLocation = GetPlayerTank()->GetActorLocation();
	if (HitLocation != FVector(0))
	{	
		GetControlledTank()->AimAt(HitLocation);

		// TODO Fire if ready
	 }
	
	return;
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	if (Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}
	else
	{
		return nullptr;
	}
}
