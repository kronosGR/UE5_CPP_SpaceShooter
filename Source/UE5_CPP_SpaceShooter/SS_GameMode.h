// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Hazard.h"
#include "GameFramework/GameMode.h"
#include "SS_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CPP_SPACESHOOTER_API ASS_GameMode : public AGameMode
{
	GENERATED_BODY()


	ASS_GameMode();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> Enemy;


	UPROPERTY(EditAnywhere)
	TSubclassOf<AHazard> HazardTemplate;

	UPROPERTY(EditAnywhere)
	UAudioComponent* MusicTrack;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	TSubclassOf<AHazard> GetHazardTemplate();

public:
	int32 SpawnTimer;
	bool bPlayerDead;

	UFUNCTION()
	void RestartLevel(FName LevelName);

	bool bStart;

protected:
	FActorSpawnParameters AsteroidSpawnParameters;
	FVector AsteroidSpawnLoc;
	FRotator AsteroidSpawnRot;

	UWorld* ThisWorld;
};
