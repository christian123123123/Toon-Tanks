// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank() {

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}


void ATank::Move(float Value) {

	FVector DeltaLocation = FVector::ZeroVector;

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaLocation.X = Value * Speed * DeltaTime;

	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value) {
	FRotator DeltaRotation = FRotator::ZeroRotator;

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaRotation.Yaw = Value * DeltaTime * RotationSpeed;

	AddActorLocalRotation(DeltaRotation);
}

void ATank::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (PlayerControllerRef) {
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction() {
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

APlayerController* ATank::GetPlayerController() const {
	return PlayerControllerRef;
}

