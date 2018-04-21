// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	

public:

protected:
	
private:
	virtual void BeginPlay();
	virtual void Tick(float) override;

	// How close shall the AI tank get
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 5000;	// TODO check radius is in cm
};
