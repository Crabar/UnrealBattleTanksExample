// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	FVector2D GetCrosshairLocation() const;

public:
	ATank* GetControlledTank() const;

	UPROPERTY(EditAnywhere)
	float AimRange = 20000.f;
};
