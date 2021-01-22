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
bool UInventoryComponent::AddItemIndx(class UItemBase* Item, int32 Index)
{
	if(!Items[Index]){
		Items[Index]=Item;
		Item->OwningInventory=this;
		Item->World=GetWorld();
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

bool UInventoryComponent::RemoveItem(class UItemBase* Item){
	for(int32 i=0;i<Size.X*Size.Y;i++){
		if(Items[i]==Item){
			Items[i]->ConditionalBeginDestroy();
			Items[i]=nullptr;
			OnInventoryUpdated.Broadcast();
			return true;
		}
	}
	OnInventoryUpdated.Broadcast();
	return false;
}

bool UInventoryComponent::RemoveItems(class UItemBase* Item, int32 Quantity){
	for(int32 i=0;i<Size.X*Size.Y;i++){
		if(Items[i]){
			if(Items[i]->IDName.EqualTo(Item->IDName,ETextComparisonLevel::Default)){
				if(Quantity>=Items[i]->Quantity){
					Quantity-=Items[i]->Quantity;
					AActor* Player=GetOwner();
					if(Player){
						if(Player->FindComponentByClass<class UInputStateMachine>())
							if(Player->FindComponentByClass<class UInputStateMachine>()->EquippedQuickSlot==i)
								Player->FindComponentByClass<class UInputStateMachine>()->UnequipItem();
					}
					Items[i]->ConditionalBeginDestroy();
					Items[i]=nullptr;
				}
				else{
					Items[i]->Quantity-=Quantity;
					Quantity=0;
					OnInventoryUpdated.Broadcast();
					return true;
				}
			}
		}
	}
	OnInventoryUpdated.Broadcast();
	return false;
}

bool UInventoryComponent::RemoveItemFromSlot(int32 Index)
{
	if(Items[Index]){
		Items[Index]->OwningInventory=nullptr;
		Items[Index]->World=nullptr;
		Items[Index]=nullptr;
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

int32 UInventoryComponent::GetItemQuantity(class UItemBase* Item){
	int32 Q=0;
	for(int32 i=0;i<Size.X*Size.Y;i++){
		if(Items[i]){
			if(Items[i]->IDName.EqualTo(Item->IDName,ETextComparisonLevel::Default)){
				Q+=Items[i]->Quantity;
			}
		}
	}
	return Q;
}