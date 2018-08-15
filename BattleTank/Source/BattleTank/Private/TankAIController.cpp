// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("Unable to locate Player Controller from AI Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI has found %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		// TODO Move towards the player

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// TODO Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}




