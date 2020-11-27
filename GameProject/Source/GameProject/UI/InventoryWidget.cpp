// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void UInventoryWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(InvCanva){
        InvCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UInventoryWidget::ShowInventory(){
    if(InvCanva){
        if(InvCanva->Visibility == ESlateVisibility::Hidden){
            InvCanva->SetVisibility(ESlateVisibility::Visible);
        }
    }
}
void UInventoryWidget::HideInventory(){
    if(InvCanva){
        InvCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}
