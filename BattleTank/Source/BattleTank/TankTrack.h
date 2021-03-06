// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Used to apply forces to tank / tank track
 */
UCLASS(meta = (BlueprintSpawnableComponent)) 
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// Max Force per Track in Newton
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000;

private:
	UTankTrack();
	virtual void BeginPlay() override;
	//void OnRegister();
	void ApplySidewaysForce();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void DriveTrack();
	float CurrentThrottle = 0;
 };
