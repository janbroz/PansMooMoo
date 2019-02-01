// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"
#include "Blueprint/UserWidget.h"
#include "Store.generated.h"

/**
 * 
 */
UCLASS()
class PANSMOOMOO_API AStore : public ABuilding
{
	GENERATED_BODY()
public:
	AStore();

	virtual void BeginPlay() override;

	// Show the store widget to the player.
	void ShowStoreWidget(class AHeroPlayerController* HeroController);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> StoreWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
		class UUserWidget* StoreWidget;
};
