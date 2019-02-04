// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "Components/BillboardComponent.h"
#include "Enemies/Enemy.h"
#include "TimerManager.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject< UBillboardComponent>(TEXT("Sprite component"));
	if (SpriteComponent && SpriteTexture)
	{
		SpriteComponent->Sprite = SpriteTexture;
		SpriteComponent->SetupAttachment(RootComponent);
	}

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &ASpawner::SpawnWave, WaveCooldown, true, 15.f);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawner::SpawnWave()
{
	if(CurrentWave >= MaxWaves)
	{
		GetWorldTimerManager().ClearTimer(WaveTimerHandle);
	}
	else
	{
		EnemiesSpawned = 0;
		SpawnMinions();
	}
}

void ASpawner::SpawnMinions()
{
	if (EnemyClass)
	{
		if (EnemiesSpawned < EnemiesToSpawn)
		{
			FActorSpawnParameters FASP;
			AEnemy* SpawnedMinion = GetWorld()->SpawnActor<AEnemy>(EnemyClass, GetActorTransform(),FASP);
			if (SpawnedMinion)
			{
				SpawnedMinion->SpawnDefaultController();
				EnemiesSpawned++;
				if (EnemiesSpawned < EnemiesToSpawn)
				{
					SpawnMinions();
				}
				else
				{
					CurrentWave++;
				}
			}
		}
	}
}
