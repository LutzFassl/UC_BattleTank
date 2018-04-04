// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories =("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate (float DegreesPerSecond);



private:
	
	UPROPERTY(EditAnywhere, Category = BarrelBoundaries)
	float MaxDegreesPerSecond = 20.f;
	
	UPROPERTY(EditAnywhere, Category = BarrelBoundaries)
	float MaxDegreesElevation = 20.f;

	UPROPERTY(EditAnywhere, Category = BarrelBoundaries)
	float MinDegreesElevation = 0.f;
	
	
};
