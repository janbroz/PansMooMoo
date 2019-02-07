// Fill out your copyright notice in the Description page of Project Settings.

#include "PansMooMooGameModeBase.h"
#include "Player/HeroPlayerController.h"
#include "Player/MooPlayerState.h"
#include "Player/Hero.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "Enemies/Spawner.h"

APansMooMooGameModeBase::APansMooMooGameModeBase()
{
	static ConstructorHelpers::FObjectFinder<UClass> Dummy_BP(TEXT("/Game/Characters/Dummy/Blueprint/Dummy.Dummy_C"));
	if (Dummy_BP.Object)
	{
		DefaultPawnClass = Dummy_BP.Object;
	}
	PlayerControllerClass = AHeroPlayerController::StaticClass();
	PlayerStateClass = AMooPlayerState::StaticClass();

	//DefaultPawnClass = AHero::StaticClass();
}

void APansMooMooGameModeBase::StartPlay()
{
	Super::StartPlay();

	PrepareWave();
}

void APansMooMooGameModeBase::StartWave()
{
	for (TActorIterator<ASpawner> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ASpawner* Spawner = *ActorItr;
		if (Spawner)
		{
			Spawner->SpawnWave(CurrentWave);
		}
	}
}

void APansMooMooGameModeBase::PrepareWave()
{
	CurrentWave++;
	GetWorldTimerManager().SetTimer(TimerHandleWave, this, &APansMooMooGameModeBase::StartWave, 20.f, true);
}
