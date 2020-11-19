// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"

UDialogWidget::UDialogWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
    
}

void UDialogWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(TXTDialog)
        TXTDialog->SetVisibility(ESlateVisibility::Hidden);
    if(DialogCanva)
        DialogCanva->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogWidget::UpdateComboCount(int32 Value){
    if(TXTDialog){
        //turn text box visible if it wasn't
        if(TXTDialog->Visibility == ESlateVisibility::Hidden){
            TXTDialog->SetVisibility(ESlateVisibility::Visible);
            DialogCanva->SetVisibility(ESlateVisibility::Visible);
        }
        TXTDialog->SetText(FText::FromString(FString::FromInt(Value)+"x Combo"));
        
        if(DialogFadeInAnim){
            PlayAnimation(DialogFadeInAnim,0.f,1,EUMGSequencePlayMode::Forward,1.f);
        }
    }
}

void UDialogWidget::ResetComboCount(){
    if(TXTDialog){
        TXTDialog->SetVisibility(ESlateVisibility::Hidden);
        DialogCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UDialogWidget::PlayDialogFadeAnim(){
    if(DialogFadeOutAnim){
        PlayAnimation(DialogFadeOutAnim,0.f,1,EUMGSequencePlayMode::Forward,1.f);
    }
}

