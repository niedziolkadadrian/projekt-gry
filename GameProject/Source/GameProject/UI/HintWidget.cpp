// Fill out your copyright notice in the Description page of Project Settings.


#include "HintWidget.h"

UHintWidget::UHintWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void UHintWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(HintCanva)
        HintCanva->SetVisibility(ESlateVisibility::Hidden);
}

void UHintWidget::ShowHint(FText Value){
    if(HintCanva && TXTHint){
        if(HintCanva->Visibility == ESlateVisibility::Hidden){
            HintCanva->SetVisibility(ESlateVisibility::Visible);
        }
        TXTHint->SetText(Value);
    }
}
void UHintWidget::HideHint(){
    if(HintCanva && TXTHint){
        HintCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

