// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Component"));
	ExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion FX"));
	ExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Explosion Sound"));

	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionFX->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}


// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::OnBeginOverlap(AActor* EnemyActor, AActor* OtherActor)
{
}
