// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItem.h"

void UFoodItem::OnUse_Implementation(class AGameProjectCharacter* Character){
    if(Character){
        Character->Hunger+=HungerToRecover;
    }
}