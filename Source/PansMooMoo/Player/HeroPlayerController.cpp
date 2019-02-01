// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroPlayerController.h"
#include "Hero.h"
#include "Buildings/Building.h"
#include "Buildings/Store.h"

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
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, true, Hit);
	if (Hit.bBlockingHit)
	{
		ABuilding* ClickedBuilding = Cast<ABuilding>(Hit.GetActor());
		// Check if the player clicked a store or if he wants to attack.
		if (ClickedBuilding)
		{
			// Is it a building what we clicked?
			if (ClickedBuilding->IsPlayerCloseEnough(GetPawn()))
			{
				AStore* Store = Cast<AStore>(ClickedBuilding);
				if (Store)
				{
					Store->ShowStoreWidget(this);
				}

				UE_LOG(LogTemp, Warning, TEXT("Player is close enough"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("You are too far away from the store"));
			}
		}
		else
		{
			// It might be a unit

			UE_LOG(LogTemp, Warning, TEXT("Nigga, you clicked something else"));
		}
	}


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

