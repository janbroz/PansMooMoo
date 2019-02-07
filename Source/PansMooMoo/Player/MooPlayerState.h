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
	UFUNCTION(BlueprintCallable)
		bool BuyItem(int32 Price);

public:
	UPROPERTY(VisibleAnywhere)
		uint32 bHasHeroSelected : 1;
	UPROPERTY(VisibleAnywhere)
		uint32 bHasHeroAlive : 1;
	UPROPERTY(VisibleAnywhere)
		int32 Level;
	UPROPERTY(VisibleAnywhere)
		int32 CurrentExperience;
	UPROPERTY(VisibleAnywhere)
		int32 Gold;
	UPROPERTY(VisibleAnywhere)
		int32 SpecialCurrency;

	

};
