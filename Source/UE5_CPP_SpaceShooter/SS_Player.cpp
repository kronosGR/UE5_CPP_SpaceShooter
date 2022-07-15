// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Player.h"

#include "NavigationSystemTypes.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASS_Player::ASS_Player()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	ExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionFX"));
	DeathExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathExplosionSound"));

	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ShipMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleSystem->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	DeathExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MaxVelocity = 250.f;
	Current_X_Velocity = 0.f;
	Current_Y_Velocity = 0.f;

	bIsFiring = false;
	WeaponFireRate = 0.25f;
	TimeSinceLastShot = 0.f;

	PlayerScore = 0.f;
}


// Called when the game starts or when spawned
void ASS_Player::BeginPlay()
{
	Super::BeginPlay();

	Current_Location = this->GetActorLocation();
	Current_Rotation = this->GetActorRotation();

	bHit = false;
	bDead = false;

	ExplosionFX->Deactivate();
	DeathExplosionSound->Deactivate();

	Max_Health = 100.f;
	Current_Health = 100.f;

	Max_Armor = 100.f;
	Current_Armor = 100.f;

	OnActorBeginOverlap.AddDynamic(this, &ASS_Player::OnBeginOverlap);
}

// Called every frame
void ASS_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Current_X_Velocity != 0.f || Current_Y_Velocity != 0.f)
	{
		New_Location = FVector(Current_Location.X + (Current_X_Velocity * DeltaTime),
		                       Current_Location.Y + (Current_Y_Velocity * DeltaTime), 0.f);

		this->SetActorLocation(New_Location);
		Current_Location = New_Location;
	}

	if (Current_Y_Velocity > 0.1f)
	{
		this->SetActorRotation(FRotator(Current_Rotation.Pitch + 45.0f, Current_Rotation.Yaw, Current_Rotation.Roll));
	}
	else if (Current_Y_Velocity < -0.1f)
	{
		this->SetActorRotation(FRotator(Current_Rotation.Pitch + 45.0f, Current_Rotation.Yaw, Current_Rotation.Roll));
	}
	else
	{
		this->SetActorRotation(FRotator(Current_Rotation));
	}
}

// Called to bind functionality to input
void ASS_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ASS_Player::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ASS_Player::MoveUp);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASS_Player::FireWeapon);
}


void ASS_Player::MoveRight(float AxisValue)
{
	Current_X_Velocity = MaxVelocity * AxisValue;
}

void ASS_Player::MoveUp(float AxisValue)
{
	Current_Y_Velocity = MaxVelocity * AxisValue;
}

void ASS_Player::FireWeapon()
{
}

void ASS_Player::StartFiring()
{
}

void ASS_Player::StopFiring()
{
}

void ASS_Player::OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor)
{
}

void ASS_Player::CollectablePickUp()
{
}
