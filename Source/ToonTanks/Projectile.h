// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	class UProjectileMovementComponent* ProjectileMoveComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category= "Animations")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UParticleSystemComponent* FireParticlesComp;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category ="Camera")
	TSubclassOf<UCameraShakeBase> HitCameraShake;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
