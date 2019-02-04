// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class PANSMOOMOO_API ASpawner : public AActor
{
	GENERATED_BODY()
	// This class manages the enemy spawns.

public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnWave();
	void SpawnMinions();

public:
	// Spawner information
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner configuration")
		uint32 bIsActive : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner configuration")
		float Radious = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner configuration")
		int32 EnemiesToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner configuration")
		int32 EnemiesSpawned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner configuration")
		int32 Cooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner configuration")
		TArray<AActor*> EnemiesSpawnedRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner configuration")
		UBillboardComponent* SpriteComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner configuration")
		UTexture2D* SpriteTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner configuration")
		TSubclassOf<class AEnemy> EnemyClass;
	
	// Handler for the timer
	FTimerHandle WaveTimerHandle;

	// FOR TESTING ONLY, IT SHOULD BE DONE FROM GAME STATE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner configuration")
		int32 CurrentWave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner configuration")
		int32 MaxWaves;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner configuration")
		int32 WaveCooldown;
};
