// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "SS_Player.generated.h"

UCLASS()
class UE5_CPP_SPACESHOOTER_API ASS_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASS_Player();

	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ExplosionFX;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ShipMesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
	UAudioComponent* DeathExplosionSound;

	UPROPERTY(EditAnywhere)
	float Field_Width;
	
	UPROPERTY(EditAnywhere)
	float Field_Height;
	
	UPROPERTY(BlueprintReadOnly)
	float Max_Health;
	
	UPROPERTY(BlueprintReadOnly)
	float Current_Health;
	
	UPROPERTY(BlueprintReadOnly)
	float Max_Armor;
	
	UPROPERTY(BlueprintReadOnly)
	float Current_Armor;

	void MoveRight(float AxisValue);
	void MoveUp(float AxisValue);

	void FireWeapon();
	void StartFiring();
	void StopFiring();
	

	UPROPERTY(EditAnywhere)
	float MaxVelocity;

	bool bIsFiring;
	float WeaponFireRate;
	float TimeSinceLastShot;

	bool bHit;
	bool bDead;

	float Current_X_Velocity;
	float Current_Y_Velocity;

	
	UPROPERTY(BlueprintReadOnly)
	float PlayerScore;

	FVector Current_Location;
	FRotator Current_Rotation;
	FVector New_Location;

	UFUNCTION()
	void OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor);

	
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<AProjectile> WeaponProjectile_BP;

	void CollectablePickUp();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
