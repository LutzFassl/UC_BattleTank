// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);



UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = Health)		//BlueprintPure does not affect owning object. Like a "Blueprintcallable Readonly"
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

protected:

private:
	ATank();

	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = Health)
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Health)
	int32 CurrentHealth = StartingHealth;

	
	
};
