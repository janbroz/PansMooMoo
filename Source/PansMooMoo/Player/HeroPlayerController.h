// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HeroPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PANSMOOMOO_API AHeroPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AHeroPlayerController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UFUNCTION()
		void VerticalMovement(float Amount);
	UFUNCTION()
		void HorizontalMovement(float Amount);
	UFUNCTION()
		void LeftMouseButtonPressed();
	UFUNCTION()
		void RightMouseButtonPressed();
	UFUNCTION()
		void AlignMouse();

	// Interaction
	void AttackEnemy(AActor* Enemy);

	// Networking functions
	UFUNCTION(Reliable, Server, WithValidation)
		void Server_AttackEnemy(AActor* Enemy);

public:
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class UHeroWidget> HUDWidgetClass;
	UPROPERTY(VisibleAnywhere)
		class UHeroWidget* HUDWidget;

};
