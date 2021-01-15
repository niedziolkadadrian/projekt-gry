// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingItem.h"

void UBuildingItem::OnUse_Implementation(class AActor* Character){

}

void UBuildingItem::OnEquip_Implementation(class AActor* Character){
    
    UBuildingSystemComponent* BuildingComponent=Character->FindComponentByClass<UBuildingSystemComponent>();
    if(BuildingComponent){
        BuildingComponent->StartBuildingMode();
    }
}

void UBuildingItem::OnUnEquip_Implementation(class AActor* Character){
    UBuildingSystemComponent* BuildingComponent=Character->FindComponentByClass<UBuildingSystemComponent>();
    if(BuildingComponent){
        BuildingComponent->EndBuildingMode();
    }
}