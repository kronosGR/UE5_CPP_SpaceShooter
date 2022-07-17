// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_GameMode.h"

#include "Components/AudioComponent.h"

ASS_GameMode::ASS_GameMode()
{
	SpawnTimer = 0.f;

	MusicTrack = CreateDefaultSubobject<UAudioComponent>(TEXT("Music"));
	MusicTrack->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	AsteroidSpawnLoc = FVector(1000.f, 1000.f, 1000.f);
	AsteroidSpawnRot = FRotator(0.f, 0.f, 0.f);

	ThisWorld = GetWorld();
}

void ASS_GameMode::BeginPlay()
{
	Super::BeginPlay();

	MusicTrack->Play();
	bPlayerDead = false;
}

void ASS_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SpawnTimer = FMath::RandRange(0, 1000);

	if (Enemy)
	{
		if (SpawnTimer > 990)
		{
			FVector EnemySpawnLoc(0.f, 0.f, 0.f);
			FRotator EnemySpawnRot(0.f, 0.f, 0.f);

			AActor* NewEnemy = ThisWorld->SpawnActor(Enemy, &EnemySpawnLoc, &EnemySpawnRot, AsteroidSpawnParameters);

			if (NewEnemy)
			{
				NewEnemy->SetActorLocation(FVector(1000.f, FMath::RandRange(-500, 500), 0.f));
			}
		}
	}

	if (HazardTemplate)
	{
		if (SpawnTimer > 995)
		{
			AActor* NewHazard = ThisWorld->SpawnActor(HazardTemplate, &AsteroidSpawnLoc, &AsteroidSpawnRot,
			                                          AsteroidSpawnParameters);

			if (NewHazard)
			{
				NewHazard->SetActorLocation(FVector(1000.f, 1000.f, 1000.f));
			}
		}
	}
}

TSubclassOf<AHazard> ASS_GameMode::GetHazardTemplate()
{
	return nullptr;
}

void ASS_GameMode::RestartLevel(FName LevelName)
{
}
