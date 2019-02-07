// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PANSMOOMOO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void InitializeInventory();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Add an item to the inventory
	UFUNCTION(BlueprintCallable)
		void AddItem(class AItem* NewItem);
	UFUNCTION(BlueprintCallable)
		void RemoveItem(int32 Index);
	UFUNCTION(BlueprintCallable)
		void UseItem(int32 Index);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		TArray<class AItem*> Inventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		int32 MaxSlots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		int32 UsedSlots;

};
