// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	auto isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!Barrel || !isReloaded)
	{
		return;
	}

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
										Barrel->GetSocketLocation(FName("Projectile")),
	                                    Barrel->GetSocketRotation(FName("Projectile")));

	Projectile->Launch(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}

void ATank::AimAt(FVector TargetLocation) const
{
	TankAimingComponent->AimAt(TargetLocation, LaunchSpeed);
}
