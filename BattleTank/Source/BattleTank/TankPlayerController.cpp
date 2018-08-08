// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController() {
	// Allow on tick
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("No controlled tank found on Player Controller."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player is controlling %s"), *ControlledTank->GetName());
	}

}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank) { return; }
	// Get world location if linetrace through crosshair 
	// If it hits the landscape
		// Tell controlled tank to aim at this point.
}

