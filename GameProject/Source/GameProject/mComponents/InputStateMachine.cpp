// Fill out your copyright notice in the Description page of Project Settings.


#include "InputStateMachine.h"

// Sets default values for this component's properties
UInputStateMachine::UInputStateMachine()
{
	PrimaryComponentTick.bCanEverTick = false;
	EquippedQuickSlot=0;
	LastEquippedItem=nullptr;
}


// Called when the game starts
void UInputStateMachine::BeginPlay()
{
	Super::BeginPlay();
	ActState=InputState::PlayerInput;
	BeforeUI=InputState::PlayerInput;
	
	AActor* Actor=GetOwner();
	if(Actor){
		if(Actor->InputComponent){
			Actor->InputComponent->BindAction("QuickSlot1", IE_Pressed,  this, &UInputStateMachine::QuickSlot1);
			Actor->InputComponent->BindAction("QuickSlot2", IE_Pressed,  this, &UInputStateMachine::QuickSlot2);
			Actor->InputComponent->BindAction("QuickSlot3", IE_Pressed,  this, &UInputStateMachine::QuickSlot3);
			Actor->InputComponent->BindAction("QuickSlot4", IE_Pressed,  this, &UInputStateMachine::QuickSlot4);
			Actor->InputComponent->BindAction("QuickSlot5", IE_Pressed,  this, &UInputStateMachine::QuickSlot5);
			Actor->InputComponent->BindAction("QuickSlot6", IE_Pressed,  this, &UInputStateMachine::QuickSlot6);

			Actor->InputComponent->BindAction("UseEquippedItem", IE_Pressed,  this, &UInputStateMachine::UseEquippedItem);
		}	
	}
}
void UInputStateMachine::UnequipItem(){
	AActor* Player=GetOwner();
	if(Player){
		UInventoryComponent* Inventory=Player->FindComponentByClass<UInventoryComponent>();
		if(Inventory){
			if(LastEquippedItem){
				LastEquippedItem->OnUnEquip(Player);
			}
		}
		LastEquippedItem=nullptr;
	}
}

void UInputStateMachine::RefreshEquippedItem(){
	AActor* Player=GetOwner();
	if(Player){
		UInventoryComponent* Inventory=Player->FindComponentByClass<UInventoryComponent>();
		if(Inventory){
			if(LastEquippedItem){
				LastEquippedItem->OnUnEquip(Player);
			}
			if(Inventory->Items[EquippedQuickSlot]){
				Inventory->Items[EquippedQuickSlot]->OnEquip(Player);
			}
			LastEquippedItem=Inventory->Items[EquippedQuickSlot];
		}
	}
}

void UInputStateMachine::QuickSlot1(){
	if(ActState==InputState::PlayerInput ||
	   ActState==InputState::Building)
	{
		EquippedQuickSlot=0;
		RefreshEquippedItem();
		OnQuickSlotChanged.Broadcast();
	}
}
void UInputStateMachine::QuickSlot2(){
	if(ActState==InputState::PlayerInput ||
	   ActState==InputState::Building)
	{
		EquippedQuickSlot=1;
		RefreshEquippedItem();
		OnQuickSlotChanged.Broadcast();
	}
}
void UInputStateMachine::QuickSlot3(){
	if(ActState==InputState::PlayerInput ||
	   ActState==InputState::Building)
	{
		EquippedQuickSlot=2;
		RefreshEquippedItem();
		OnQuickSlotChanged.Broadcast();
	}
}
void UInputStateMachine::QuickSlot4(){
	if(ActState==InputState::PlayerInput ||
	   ActState==InputState::Building)
	{
		EquippedQuickSlot=3;
		RefreshEquippedItem();
		OnQuickSlotChanged.Broadcast();
	}
}
void UInputStateMachine::QuickSlot5(){
	if(ActState==InputState::PlayerInput ||
	   ActState==InputState::Building)
	{
		EquippedQuickSlot=4;
		RefreshEquippedItem();
		OnQuickSlotChanged.Broadcast();
	}
}
void UInputStateMachine::QuickSlot6(){
	if(ActState==InputState::PlayerInput ||
	   ActState==InputState::Building)
	{
		EquippedQuickSlot=5;
		RefreshEquippedItem();
		OnQuickSlotChanged.Broadcast();
	}
}

void UInputStateMachine::UseEquippedItem(){
	if(ActState==InputState::PlayerInput ||
	   ActState==InputState::Building)
	{
		AActor* Player=GetOwner();
		if(Player){
			UInventoryComponent* Inventory=Player->FindComponentByClass<UInventoryComponent>();
			if(Inventory){
				if(Inventory->Items[EquippedQuickSlot]){
					Inventory->Items[EquippedQuickSlot]->OnUse(Player);
				}
			}
		}
	}
}