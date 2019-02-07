// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroPlayerController.h"
#include "Hero.h"
#include "Buildings/Building.h"
#include "Buildings/Store.h"
#include "Enemies/Enemy.h"
#include "Widgets/Player/HeroWidget.h"
#include "UObject/ConstructorHelpers.h"

AHeroPlayerController::AHeroPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UClass> HUDWidgetClass_BP(TEXT("/Game/UI/HUD/PlayerHUD.PlayerHUD_C"));
	if (HUDWidgetClass_BP.Object)
	{
		HUDWidgetClass = HUDWidgetClass_BP.Object;
	}
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

void AHeroPlayerController::BeginPlay()
{
	if (HUDWidgetClass && IsLocalController())
	{
		HUDWidget = CreateWidget<UHeroWidget>(this, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
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
	// This is coded for a single player session, have to add multiplayer
	// and server validation for when other players are connecting.
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
			AEnemy* ClickedEnemy = Cast<AEnemy>(Hit.GetActor());
			if (ClickedEnemy)
			{
				AttackEnemy(ClickedEnemy);
				

				
			}
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

void AHeroPlayerController::AttackEnemy(AActor* Enemy)
{
	if (Role < ROLE_Authority)
	{
		Server_AttackEnemy(Enemy);
	}
	else
	{
		FVector Difference = Enemy->GetActorLocation() - GetPawn()->GetActorLocation();
		float Distance = Difference.Size();
		if (Distance <= 400.f)
		{
			Enemy->Destroy();
		}
	}
}

void AHeroPlayerController::Server_AttackEnemy_Implementation(AActor* Enemy)
{
	AttackEnemy(Enemy);
}

bool AHeroPlayerController::Server_AttackEnemy_Validate(AActor* Enemy)
{
	return true;
}

