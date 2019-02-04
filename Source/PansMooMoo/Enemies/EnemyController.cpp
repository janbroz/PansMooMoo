// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "Enemies/Enemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AEnemyController::AEnemyController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
	BrainComponent = BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void AEnemyController::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Im controlling this mothafucker"));
}

void AEnemyController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AEnemy* EnemyPawn = Cast<AEnemy>(InPawn);
	if (EnemyPawn && EnemyPawn->EnemyBehaviour)
	{
		if (EnemyPawn->EnemyBehaviour->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*EnemyPawn->EnemyBehaviour->BlackboardAsset);
			BlackboardComp->SetValueAsVector(FName(TEXT("Destiny")), FVector(0,0,0));
		}
		BehaviorComp->StartTree(*EnemyPawn->EnemyBehaviour);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("We got a problem here"));
	}
}

