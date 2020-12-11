// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingWidget.h"

UCraftingWidget::UCraftingWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void UCraftingWidget::NativeConstruct(){
    Super::NativeConstruct();
    /*if(CraftingCanva){
        CraftingCanva->SetVisibility(ESlateVisibility::Hidden);
    }*/
}

void UCraftingWidget::ShowCrafting(){
    if(CraftingCanva){
        if(CraftingCanva->Visibility == ESlateVisibility::Hidden){
            CraftingCanva->SetVisibility(ESlateVisibility::Visible);
        }
    }
}
void UCraftingWidget::HideCrafting(){
    if(CraftingCanva){
        CraftingCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UCraftingWidget::Update(UInventoryComponent* Inventory){

}