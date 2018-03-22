// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
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
