// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
class UTankBarrel;
class UTankTurret;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector, float);
	void SetBarrelReference(UTankBarrel * BarrelToSet) ;
	void SetTurretReference(UTankTurret * TurretToSet);

protected:


private:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	void MoveBarrelTowards(FVector);
	void MoveTurretTowards(FVector);



		
	
};
