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

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	float CrosshairXLocation = 0.5;
	float CrosshairYLocation = 1.0 / 3.0;
	auto CrosshairLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);


	FHitResult HitResult;
	const auto IsHit = GetOwner()->ActorLineTraceSingle(HitResult);

	if (IsHit)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}

