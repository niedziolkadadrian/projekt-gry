// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemWidget.h"

UInventoryItemWidget::UInventoryItemWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void UInventoryItemWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(QuickActionBox){
        QuickActionBox->SetVisibility(ESlateVisibility::Hidden);
    }
    if(ItemQuantityBox){
        ItemQuantityBox->SetVisibility(ESlateVisibility::Hidden);
    }
    if(ItemImage){
        ItemImage->SetVisibility(ESlateVisibility::Hidden);
    }
}