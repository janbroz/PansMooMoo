// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PansMooMooGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PANSMOOMOO_API APansMooMooGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APansMooMooGameModeBase();

	virtual void StartPlay() override;

protected:
	void StartWave();
	void PrepareWave();

protected:
	int32 CurrentWave;
	FTimerHandle TimerHandleWave;
	FTimerHandle TimerHandleMinionSpawn;
};
