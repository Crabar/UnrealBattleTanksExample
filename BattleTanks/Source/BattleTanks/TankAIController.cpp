// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No tank in AIController"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController has a %s"), *ControlledTank->GetName());
	}

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController aimed to a %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());

	if (TankPlayerController)
	{
		return TankPlayerController->GetControlledTank();
	}

	return nullptr;
}

