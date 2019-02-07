// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	MaxSlots = 6;
	UsedSlots = 0;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InitializeInventory();
}


void UInventoryComponent::InitializeInventory()
{
	for (int32 i = 0; i< MaxSlots; ++i)
	{
		Inventory.Add(nullptr);
	}
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(class AItem* NewItem)
{
	if (UsedSlots < MaxSlots)
	{
		for (auto& Item : Inventory)
		{
			if (Item == nullptr)
			{
				Item = NewItem;
				UsedSlots++;
				break;
			}
		}
	}
}

void UInventoryComponent::RemoveItem(int32 Index)
{
	AItem* SelectedItem = Inventory[Index];


}

void UInventoryComponent::UseItem(int32 Index)
{

}

