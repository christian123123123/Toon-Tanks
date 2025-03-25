// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (IsInRange()) {
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::BeginPlay() {
	Super::BeginPlay();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	FString LevelName = GetWorld()->GetMapName();
	LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix); // Removes prefix like "UEDPIE_0_"

	if (LevelName == "Main"){
		FireRate = 2.0f;
	}
	else if (LevelName == "Level_02"){
		FireRate = 1.5f;
	}
	else if (LevelName == "Level_03"){
		FireRate = 1.0f;
	}
	else if(LevelName == "Level_04"){
		FireRate = 1.0f;
	}
	else if (LevelName == "Level_05") {
		FireRate = 0.2f;
	}

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this,  &ATower::CheckFireCondition, FireRate, true);

}

void ATower::CheckFireCondition() {
	if (IsInRange()) {
		Fire();
	}
}


bool ATower::IsInRange() {
	if (Tank) {
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange) {
			return true;
		}
	}
	return false;
}

void ATower::HandleDestruction() {
	Super::HandleDestruction();
	Destroy();
}
