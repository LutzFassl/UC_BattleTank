// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	//OnComponentHit
}

//void  UTankTrack::OnRegister()
//{
//	Super::OnRegister();
//	PrimaryComponentTick.bCanEverTick = true;
//}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	//UE_LOG(LogTemp, Warning, TEXT("I am ticking."));
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	//Calc slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//UE_LOG(LogTemp, Warning, TEXT("Speed vs Slip Speed: %f, %f"), GetComponentVelocity().Size(), SlippageSpeed);
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;	// divided by 2 because each track will apply it
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	// gets called every frame if tank is on the ground

	// drive tank
	DriveTrack();

	// apply sideways force
	ApplySidewaysForce();
	
	//Reset Throttle
	CurrentThrottle = 0;
	//UE_LOG(LogTemp, Warning, TEXT("I got hit. %s"), *GetName());
}

void UTankTrack::SetThrottle(float Throttle)
{
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s: throttle: %f"), *Name, Throttle);

	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

