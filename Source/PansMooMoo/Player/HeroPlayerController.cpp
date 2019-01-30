// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroPlayerController.h"
#include "Hero.h"

AHeroPlayerController::AHeroPlayerController()
{
	bShowMouseCursor = true;
}

void AHeroPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseButton", EInputEvent::IE_Pressed, this, &AHeroPlayerController::LeftMouseButtonPressed);
	InputComponent->BindAction("RightMouseButton", EInputEvent::IE_Pressed, this, &AHeroPlayerController::RightMouseButtonPressed);

	InputComponent->BindAxis("HorizontalMovement", this, &AHeroPlayerController::HorizontalMovement);
	InputComponent->BindAxis("VerticalMovement", this, &AHeroPlayerController::VerticalMovement);
}

void AHeroPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AlignMouse();
}

void AHeroPlayerController::VerticalMovement(float Amount)
{
	if (GetCharacter() && Amount != 0.f)
	{
		ACharacter* Hero = GetCharacter();
		if (Hero)
		{
			Hero->AddMovementInput(FVector::ForwardVector, Amount);
		}
	}
}

void AHeroPlayerController::HorizontalMovement(float Amount)
{
	if (GetCharacter() && Amount != 0.f)
	{
		ACharacter* Hero = GetCharacter();
		if (Hero)
		{
			Hero->AddMovementInput(FVector::RightVector, Amount);
		}
	}
}

void AHeroPlayerController::LeftMouseButtonPressed()
{

}

void AHeroPlayerController::RightMouseButtonPressed()
{

}

void AHeroPlayerController::AlignMouse()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (Hit.bBlockingHit)
	{
		FVector HeroLocation = GetCharacter()->GetActorLocation();
		FRotator LookAtRot = (Hit.Location - HeroLocation).Rotation();
		FRotator HeroRot = GetControlRotation();
		HeroRot.Yaw = LookAtRot.Yaw;
		SetControlRotation(HeroRot);
	}
}

