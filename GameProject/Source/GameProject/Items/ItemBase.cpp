// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

UItemBase::UItemBase()
{
    ItemDisplayName=FText::FromString("Item");
    UseText=FText::FromString("Use");
    StackSize=1;
    Quantity=1;
}