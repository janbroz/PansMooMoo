// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MooPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PANSMOOMOO_API AMooPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AMooPlayerState();
	
public:
	UPROPERTY(VisibleAnywhere)
		uint32 bHasHeroSelected : 1;
	UPROPERTY(VisibleAnywhere)
		uint32 bHasHeroAlive : 1;
	UPROPERTY(VisibleAnywhere)
		uint32 Level;
	UPROPERTY(VisibleAnywhere)
		uint32 CurrentExperience;
	UPROPERTY(VisibleAnywhere)
		uint32 Gold;
	UPROPERTY(VisibleAnywhere)
		uint32 SpecialCurrency;

};
