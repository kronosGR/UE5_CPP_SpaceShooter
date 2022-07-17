// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazard.h"

#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AHazard::AHazard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	AsteroidExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("AsteroidExplosionSound"));
	AsteroidExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AsteroidExplosionFX"));

	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AsteroidExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AsteroidExplosionFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AHazard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHazard::SpawnChildren(int32 NumChildren)
{
}

void AHazard::SetHazardVelocity(FVector NewVelocity)
{
}

void AHazard::OnBeginOverlap(AActor* AsteroidActor, AActor* OtherActor)
{
}

