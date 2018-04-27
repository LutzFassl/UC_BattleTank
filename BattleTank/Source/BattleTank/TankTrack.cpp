// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
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

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("I am ticking."));

	//Calc slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//UE_LOG(LogTemp, Warning, TEXT("Speed vs Slip Speed: %f, %f"), GetComponentVelocity().Size(), SlippageSpeed);
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration /2;	// divided by 2 because each track will apply it
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I got hit. %s"), *GetName());
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

