// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//void  UTankTrack::OnRegister()
//{
//	Super::OnRegister();
//	PrimaryComponentTick.bCanEverTick = true;
//}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("I am ticking."));

	//Calc slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	UE_LOG(LogTemp, Warning, TEXT("Speed vs Slip Speed: %f, %f"), GetComponentVelocity().Size(), SlippageSpeed);
	// Work out required accelration this frame to correct
	float a = -SlippageSpeed / 0.5;
	// Calculate and appliy sideways force F = m*a
	float Force = a * 40000;
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(GetRightVector()*SlippageSpeed, GetComponentLocation());
}

void UTankTrack::SetThrottle(float Throttle)
{
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s: throttle: %f"), *Name, Throttle);

	// TODO clamp actual throttle value so player can't cheat
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
		
}

