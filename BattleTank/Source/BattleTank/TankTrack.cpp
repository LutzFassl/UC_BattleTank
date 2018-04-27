// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void  UTankTrack::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("I am ticking."));
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

