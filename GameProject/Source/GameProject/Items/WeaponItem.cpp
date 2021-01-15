// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"

UWeaponItem::UWeaponItem(){
    AttackDamage=20.f;
    NumberOfUses=100;
}

void UWeaponItem::OnUse_Implementation(class AActor* Character){

}

void UWeaponItem::OnEquip_Implementation(class AActor* Character){

}

void UWeaponItem::OnUnEquip_Implementation(class AActor* Character){
    
}