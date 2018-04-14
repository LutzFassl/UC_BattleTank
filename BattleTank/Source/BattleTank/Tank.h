// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent; 
class UTankMovementComponent;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector);

	UFUNCTION(BlueprintCallable, Category = Setup)	// can be called from BP
	void SetAimingComponent(UTankAimingComponent * AimingComponentToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)	// can be called from BP
	UTankAimingComponent* GetAimingComponent();

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	FString GetRemainingReload();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;
	//UClass* ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 15000.f;	// 100000 = 1000 m/s;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;	// seconds

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent * TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent * TankMovementComponent = nullptr;

	UPROPERTY(BlueprintReadWrite)
	UTankBarrel* Barrel = nullptr;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//void Tick(float DeltaTime);
	
	double LastFireTime = 0;

	
	
};
