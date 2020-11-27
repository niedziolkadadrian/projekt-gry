// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"

AInGameHUD::AInGameHUD(){

}

void AInGameHUD::BeginPlay(){
    Super::BeginPlay();
    if(DialogWidgetClass){
        dialogWidget = CreateWidget<UDialogWidget>(GetWorld(),DialogWidgetClass);
        if(dialogWidget){
            dialogWidget->AddToViewport();
        }
    }
    if(HintWidgetClass){
        hintWidget = CreateWidget<UHintWidget>(GetWorld(),HintWidgetClass);
        if(hintWidget){
            hintWidget->AddToViewport();
        }
    }
    if(InventoryWidgetClass){
        inventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(),InventoryWidgetClass);
        if(inventoryWidget){
            inventoryWidget->AddToViewport();
        }
    }
}

void AInGameHUD::Tick(float deltaSeconds){
    Super::Tick(deltaSeconds);
}

void AInGameHUD::DrawHUD(){
    Super::DrawHUD();
}


UDialogWidget* AInGameHUD::GetDialogWidget(){
    if(dialogWidget)
        return dialogWidget;
    return nullptr;
}

UHintWidget* AInGameHUD::GetHintWidget(){
    if(hintWidget)
        return hintWidget;
    return nullptr;
}

UInventoryWidget* AInGameHUD::GetInventoryWidget(){
     if(inventoryWidget)
        return inventoryWidget;
    return nullptr;
}