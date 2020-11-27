// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	Size=FVector2D(9,1);

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


bool UInventoryComponent::AddItem(class UItemBase* Item){
	if(Items.Num()>=(Size.X*Size.Y) || !Item){
		return false;
	}
	Item->OwningInventory=this;
	Item->World=GetWorld();
	Items.Add(Item);

	return true;
}

bool UInventoryComponent::RemoveItem(class UItemBase* Item){
	if(Item){
		Item->OwningInventory=nullptr;
		Item->World=nullptr;

		return true;
	}
	return false;
}
