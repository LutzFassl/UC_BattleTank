// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
//#include "Math/Vector.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, +1.f);

	// RelativeSpeed = -1..+1; DeltaTimeSeconds --> Timeindependent but Frame-Dependent - DeltaTimeSeconds = 1 / FPS, also ca. 0.01. Damit teilt er die Bewegung / sec auf die frames auf. Also Bew / Sec --> Bew / Frame
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;	
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// "stupid" way of clamping
	//if (RawNewElevation > MaxDegreesElevation) { RawNewElevation = MaxDegreesElevation; }
	//if (RawNewElevation < MinDegreesElevation) { RawNewElevation = MinDegreesElevation; }

	// ideal way of clamping
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinDegreesElevation, MaxDegreesElevation);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), GetWorld()->DeltaTimeSeconds);	//--> Time Prefix for Logging

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}



