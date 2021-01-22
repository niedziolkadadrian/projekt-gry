// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCircleWidget.h"

UActionCircleWidget::UActionCircleWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void UActionCircleWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(ActionCircleCanva){
        ActionCircleCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UActionCircleWidget::ShowActionCircle(){
    if(ActionCircleCanva){
        if(ActionCircleCanva->Visibility == ESlateVisibility::Hidden){
            ActionCircleCanva->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UActionCircleWidget::HideActionCircle(){
    if(ActionCircleCanva){
        ActionCircleCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UActionCircleWidget::Update(float r){
    Radius=r;
    SynchronizeProperties();
}

void UActionCircleWidget::SynchronizeProperties(){
    if(RadialMat && RadialMat!=LastRadialMat){
        RadialMatInst = UMaterialInstanceDynamic::Create(RadialMat, this);
        LastRadialMat=RadialMat;
    }
    if(ActionCircle){
        if(RadialMatInst){
            ActionCircle->SetBrushFromMaterial(RadialMatInst);
        }
    }
    if(RadialMatInst){
        RadialMatInst->SetScalarParameterValue("StartPoint", StartPoint);
        RadialMatInst->SetScalarParameterValue("DegreeInPercent", Radius);
        RadialMatInst->SetScalarParameterValue("InnerRadius", InnerRadius);
        RadialMatInst->SetScalarParameterValue("OuterRadius", OuterRadius);
        RadialMatInst->SetVectorParameterValue("Color",Color);
    }
}