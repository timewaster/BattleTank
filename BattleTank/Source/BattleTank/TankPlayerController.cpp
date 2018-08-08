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
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Where we lookin' nigga?: %s"), *HitLocation.ToString());
			// TODO Tell controlled tank to aim at this point.
	}
}

// Get world location of linetrace through crosshair , return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) {
	// Find crosshair position in pixel co-ordinates
	int32 ViewportSizeX, ViewportSizeY;
	FVector LookDirection;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("Where we lookin' nigga?: %s"), *LookDirection.ToString());
	}
	// line trace along that look direction and see what we hit.
	OutHitLocation = FVector(1.0);
	return true;
}

bool const ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) {
	FVector WorldLocation;
	// Deproject screen position to world direction.
	return DeprojectScreenPositionToWorld(ScreenLocation.X,
		ScreenLocation.Y, 
		WorldLocation, 
		LookDirection);
}