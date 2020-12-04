// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	Size=FIntPoint(9,1);
	InventoryName=FText::FromString("Inventory");
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Items.SetNum(Size.X*Size.Y,false);
	if(GEngine)
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), Items.Num()));   
}


bool UInventoryComponent::AddItem(class UItemBase* Item)
{
	for(int32 i=0;i<Size.X*Size.Y;i++){
		if(Items[i] && Items[i]->IDName.EqualTo(Item->IDName,ETextComparisonLevel::Default)){		//if was in inventory
			if(Items[i]->Quantity<Items[i]->StackSize){		//if stack wasn't full
				int32 howMuch=Items[i]->StackSize-Items[i]->Quantity;
				if(howMuch>Item->Quantity)					//how much i can insert to this
					howMuch=Item->Quantity;
				
				Item->Quantity-=howMuch;		//substract from this item
				Items[i]->Quantity+=howMuch;	//add to item in inventory
			}
		}
		if(Item->Quantity==0){
			//if all inserted to existing items
			OnInventoryUpdated.Broadcast();
			return true;
		}		
	}
	//if there is still something left
	for(int32 i=0;i<Size.X*Size.Y;i++){
		if(!Items[i]){	//find first empty slot
			Items[i]=Item;	//insert item there
			Item->OwningInventory=this;
			Item->World=GetWorld();
			OnInventoryUpdated.Broadcast();
			return true;
		}
	}
	OnInventoryUpdated.Broadcast();
	return false;
}
bool UInventoryComponent::AddItem(class UItemBase* Item, int32 Index)
{
	return false;
}

bool UInventoryComponent::RemoveItem(class UItemBase* Item){
	/*if(Item){
		Item->OwningInventory=nullptr;
		Item->World=nullptr;

		return true;
	}*/
	OnInventoryUpdated.Broadcast();
	return false;
}

bool UInventoryComponent::RemoveItem(class UItemBase* Item, int32 Index)
{
	return false;
}