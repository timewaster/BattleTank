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
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ATankPlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


private:
	ATank * GetControlledTank() const;
	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world.
	void AimTowardsCrosshair();
	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation);
	bool const GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection);
	bool const GetLookDirectionHitLocation(FVector LookDirection, FVector & HitLocation);
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000000;
};
