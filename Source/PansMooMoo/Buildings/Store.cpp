// Fill out your copyright notice in the Description page of Project Settings.

#include "Store.h"
#include "Player/HeroPlayerController.h"


AStore::AStore()
{
	


}

void AStore::BeginPlay()
{
	Super::BeginPlay();

	if (StoreWidget)
	{
		StoreWidget->AddToViewport();
	}
	else
	{
		if (StoreWidgetClass)
		{
			StoreWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController() ,StoreWidgetClass);
		}
	}
}

void AStore::ShowStoreWidget(AHeroPlayerController* HeroController)
{
	if (HeroController)
	{
		if (StoreWidget && !StoreWidget->IsInViewport())
		{
			StoreWidget->AddToViewport();
		}
	}
}

