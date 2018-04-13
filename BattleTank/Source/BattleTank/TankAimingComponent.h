// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
class UTankBarrel;
class UTankTurret;

UENUM()		//"BlueprintType" is essential to include
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	
	void AimAt(FVector, float);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void AimingInitialize(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;


private:
	UTankAimingComponent();
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	void MoveBarrelTowards(FVector);
	void MoveTurretTowards(FVector);

	bool bLastSolution = false;
	




		
	
};
