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
		GetControlledTank()->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair , return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) {
	// Find crosshair position in pixel co-ordinates
	int32 ViewportSizeX, ViewportSizeY;
	FVector LookDirection;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// line trace along that look direction and see what we hit.
		if (GetLookDirectionHitLocation(LookDirection, HitLocation)) {
			//UE_LOG(LogTemp, Warning, TEXT("Where we shootin' nigga?: %s"), *HitLocation.ToString());
		}
	}
	//OutHitLocation = FVector(1.0);
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

bool const ATankPlayerController::GetLookDirectionHitLocation(FVector LookDirection, FVector & HitLocation) {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams))
		{
		HitLocation = HitResult.Location;
		return 	true;
		}
	return false;
}
