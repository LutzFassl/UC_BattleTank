// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(ControlledTank && PlayerTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);	
	
	// Aim at Player
	FVector HitLocation = PlayerTank->GetActorLocation();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(HitLocation);
	if (AimingComponent->GetFiringState() == EFiringState::Locked) { AimingComponent->Fire(); }
	return;
}

