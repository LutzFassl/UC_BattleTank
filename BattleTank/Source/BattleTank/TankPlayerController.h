// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
	ATank* GetControlledTank() const;

private:
	
	ATankPlayerController();

	

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D, FVector&) const;
	bool GetLookVectorHitLocation(FVector, FVector& ) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;





	

	

	

	
	
};
