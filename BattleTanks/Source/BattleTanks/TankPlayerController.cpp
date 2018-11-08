// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No tank in PlayerController"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController has a %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{	
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

FVector2D ATankPlayerController::GetCrosshairLocation() const
{
	int ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	float CrosshairXLocation = 0.5;
	float CrosshairYLocation = 1.0 / 3.0;
	return FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	auto CrosshairLocation = GetCrosshairLocation();
	FVector CrosshairWorldLocation, LookDirection;
	auto result = DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, CrosshairWorldLocation, LookDirection);
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * AimRange);
	auto isHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);
	
	if (isHit)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}

