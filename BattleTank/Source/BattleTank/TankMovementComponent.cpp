// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }	// pointer protection
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }	// pointer protection
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO prevent double speed from double control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }	// pointer protection
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need for SUPER:: because we replace the function

	auto Name = GetOwner()->GetName();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	//My approach
	FRotator DeltaRotator = AIForwardIntention.Rotation() - TankForward.Rotation();
	float DeltaYawAngle = DeltaRotator.Yaw;
	float CalculatedThrow = cos(DeltaYawAngle);
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s reports DeltaAngle: %f, Throw: %f"), *Name, DeltaYawAngle, CalculatedThrow);
	//IntendMoveForward(CalculatedThrow);

	//Bens approach
	float ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(ForwardThrow);
}

