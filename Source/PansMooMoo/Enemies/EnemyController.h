// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class PANSMOOMOO_API AEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyController();
	virtual void Tick(float DeltaTime) override;
	virtual void Possess(APawn* InPawn) override;

public:
	class UBlackboardComponent* BlackboardComp;
	class UBehaviorTreeComponent* BehaviorComp;
};
