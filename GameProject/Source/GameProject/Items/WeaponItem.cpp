// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"

UWeaponItem::UWeaponItem(){
    AttackDamage=20.f;
    NumberOfUses=100;
}

void UWeaponItem::OnUse_Implementation(class AActor* Character){
    
    NumberOfUses-=1;
    if(GEngine)
      	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Remaining uses: %d"),NumberOfUses));
					
    if(OwningInventory){
        if(NumberOfUses==0){
            UInputStateMachine* StateMachine=Character->FindComponentByClass<UInputStateMachine>();
            if(StateMachine)
                StateMachine->UnequipItem();
            OwningInventory->RemoveItem(this);
            OwningInventory->OnInventoryUpdated.Broadcast();
        }
    }
}

void UWeaponItem::OnEquip_Implementation(class AActor* Character){

}

void UWeaponItem::OnUnEquip_Implementation(class AActor* Character){
    
}
void UWeaponItem::OnStopUse_Implementation(class AActor* Character){
    
}