// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()		//"BlueprintType" is essential to include
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	
	void AimAt(FVector);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void AimingInitialize(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet);

	UFUNCTION(BlueprintCallable)
	FString GetRemainingReload() const;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;	// seconds

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetAmountOfAmmo() const;

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable)
	void DisableBarrelMovement();

	UFUNCTION(BlueprintCallable)
	void EnableBarrelMovement();

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 15000.f;	// 100000 = 1000 m/s;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 CurrentAmmo = 10;

private:
	UTankAimingComponent();
	void MoveBarrelTowards(FVector);
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime,	enum ELevelTick TickType,FActorComponentTickFunction * ThisTickFunction) override;
	bool IsBarrelMoving();

	bool bLastSolution = false;
	double LastFireTime = 0;
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	FVector AimDirection = FVector(0);

	bool bBarrelMovementIsAllowed = true;
};
