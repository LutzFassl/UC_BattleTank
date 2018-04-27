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
	// How close shall the AI tank get
	UPROPERTY(EditAnywhere, Category = Setup)
	float AcceptanceRadius = 7000;	// TODO check radius is in cm
	
private:
	virtual void BeginPlay();
	virtual void Tick(float) override;

	
};
