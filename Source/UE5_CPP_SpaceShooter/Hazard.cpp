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

	Spawn_X_Velocity = -500.f;
	Spawn_Y_Velocity = 0.f;

	SelfDestructTime = 1.f;
	bHit = false;
}

// Called when the game starts or when spawned
void AHazard::BeginPlay()
{
	Super::BeginPlay();

	Initial_Rotation = 0.f;
	Initial_X_Locaion = 1500.f;
	Initial_Y_Location = FMath::RandRange(-500, 500);

	RandSize = FMath::RandRange(3, 8);
	this->SetActorScale3D(FVector(RandSize, RandSize, RandSize));

	AsteroidExplosionSound->Deactivate();
	// continue play even actor destroyed
	AsteroidExplosionSound->bStopWhenOwnerDestroyed = false;

	AsteroidExplosionFX->Deactivate();

	OnActorBeginOverlap.AddDynamic(this, &AHazard::OnBeginOverlap);
}

// Called every frame
void AHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(this!=nullptr);

	Initial_Rotation += DeltaTime;
	Initial_X_Locaion += DeltaTime * Spawn_X_Velocity;
	Initial_Y_Location += DeltaTime * Spawn_Y_Velocity;

	this->SetActorRotation(FRotator(Initial_Rotation * 100.f, Initial_Rotation * 50.f, 0.f));
	this->SetActorLocation(FVector(Initial_X_Locaion, Initial_Y_Location, 0.f));

	if (SelfDestructTime <= 0.f) this->Destroy();

	if (bHit)
	{
		bHit = false;
		bStartDestroyTimer = true;

		AsteroidExplosionFX->Activate();
		AsteroidExplosionFX->SetWorldLocation(this->GetActorLocation());
		AsteroidExplosionFX->SetWorldScale3D(FVector(1.f, 1.f, 1.f));

		AsteroidExplosionSound->Activate();
		AsteroidExplosionSound->Play();

		this->StaticMesh->SetVisibility(false);
		this->SetActorEnableCollision(false);

		if (this->GetActorScale3D().X > 6.f)
		{
			SpawnChildren(FMath::RandRange(3, 5));
		}
	}

	if (bStartDestroyTimer)SelfDestructTime -= DeltaTime;
}

void AHazard::SpawnChildren(int32 NumChildren)
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	for (int i = 0; i < NumChildren; i++)
	{
		if (ChildSpawn != nullptr)
		{
			AHazard* NewHazard = Cast<AHazard>(GetWorld()->SpawnActor(
				ChildSpawn, new FVector(this->GetActorLocation()),
				new FRotator(this->GetActorRotation()), Params));

			NewHazard->Initial_X_Locaion = this->GetActorLocation().X;
			NewHazard->Initial_Y_Location = this->GetActorLocation().Y;

			NewHazard->SetHazardVelocity(FVector(FMath::RandRange(-250, 100), FMath::RandRange(50, 50), 0.f));
			float RandScale = FMath::RandRange(2, 5);

			NewHazard->SetActorScale3D(FVector(RandScale, RandScale, RandScale));

			NewHazard->SetActorEnableCollision(true);
			NewHazard->StaticMesh->SetVisibility(true);
		}
	}
}

void AHazard::SetHazardVelocity(FVector NewVelocity)
{
	Spawn_X_Velocity = NewVelocity.X;
	Spawn_Y_Velocity = NewVelocity.Y;
}

void AHazard::OnBeginOverlap(AActor* AsteroidActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Bounds"))
	{
		SelfDestructTime = 0.f;
	}

	if (OtherActor->ActorHasTag("Projectile") || OtherActor->ActorHasTag("Player"))
	{
		bHit = true;
	}
}
