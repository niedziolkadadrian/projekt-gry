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
}

void AInGameHUD::Tick(float deltaSeconds){
    Super::Tick(deltaSeconds);
}

void AInGameHUD::DrawHUD(){
    Super::DrawHUD();
}

void AInGameHUD::UpdateComboCount(int32 Value){
    if(dialogWidget){
        dialogWidget->UpdateComboCount(Value);
    }
}

void AInGameHUD::ResetComboCount(){
     if(dialogWidget){
        dialogWidget->ResetComboCount();
    }
}

void AInGameHUD::PlayDialogFadeAnim(){
     if(dialogWidget){
        dialogWidget->PlayDialogFadeAnim();
    }
}