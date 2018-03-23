// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ATank* GetControlledTank() const;
	ATankPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	

private:

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	

	

	

	
	
};
