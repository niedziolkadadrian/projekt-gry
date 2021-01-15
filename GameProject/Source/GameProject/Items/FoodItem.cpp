// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItem.h"

void UFoodItem::OnUse_Implementation(class AActor* Character){
    /*Character=Cast<AGameProjectCharacter>(Character);
    if(Character){
        Character->Hunger+=HungerToRecover;
    }*/
    
    Quantity-=1;
    if(OwningInventory){
        if(Quantity==0){
            UInputStateMachine* StateMachine=Character->FindComponentByClass<UInputStateMachine>();
            if(StateMachine)
                StateMachine->UnequipItem();
            OwningInventory->RemoveItem(this);
        }
        OwningInventory->OnInventoryUpdated.Broadcast();
    }
    
}

void UFoodItem::OnEquip_Implementation(class AActor* Character){

}

void UFoodItem::OnUnEquip_Implementation(class AActor* Character){
    
}