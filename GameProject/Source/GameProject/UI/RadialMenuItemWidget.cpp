// Fill out your copyright notice in the Description page of Project Settings.


#include "RadialMenuItemWidget.h"

URadialMenuItemWidget::URadialMenuItemWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
    StartPoint=0;
    Radius=0.25f;
    InnerRadius=0.2f;
    OuterRadius=0.5f;
    BaseColor=FColor(1,1,1,1);
    SelectedColor=FColor(1,1,1,1);
    RadialMat=nullptr;
    LastRadialMat=nullptr;
    RadialMatInst=nullptr;
}

void URadialMenuItemWidget::NativeConstruct(){
    Super::NativeConstruct();
}

bool URadialMenuItemWidget::isSelected(){

    FVector2D pos;
    if(GEngine && GEngine->GameViewport )
        GEngine->GameViewport->GetViewportSize(pos);
    pos/=2;
    
    FVector2D mousePos;
    GetWorld()->GetFirstPlayerController()->GetMousePosition(mousePos.X,mousePos.Y);
    
    FVector2D vector=mousePos-pos;
    vector.Normalize();

    float localAngle=FMath::RadiansToDegrees(FGenericPlatformMath::Atan2(FGenericPlatformMath::Abs<float>(FVector2D::CrossProduct(vector,FVector2D(0,-1))),FVector2D::DotProduct(vector,FVector2D(0,-1))));
    if(FVector2D::CrossProduct(vector,FVector2D(0,-1))>0)
        localAngle=360-localAngle;
    localAngle=(localAngle)/360;
    
    if(localAngle>StartPoint && localAngle<StartPoint+Radius){
        RadialMatInst->SetVectorParameterValue("Color",SelectedColor);
        return true;
    }

    if(StartPoint+Radius>1.0f){ //on the top if even
        if((localAngle>StartPoint && localAngle<1.0) || 
            (localAngle>=0.0f && localAngle<(StartPoint+Radius-1.0f)))
        {
            RadialMatInst->SetVectorParameterValue("Color",SelectedColor);
            return true;
        }
    }
    RadialMatInst->SetVectorParameterValue("Color",BaseColor);
    return false;
}
void URadialMenuItemWidget::SynchronizeProperties(){
    Super::SynchronizeProperties();
	OnSynchronizeProperties();
}
void URadialMenuItemWidget::OnSynchronizeProperties_Implementation(){
    if(RadialMat && RadialMat!=LastRadialMat){
        RadialMatInst = UMaterialInstanceDynamic::Create(RadialMat, this);
        LastRadialMat=RadialMat;
    }
    if(RadialImg){
        if(RadialMatInst){
            RadialImg->SetBrushFromMaterial(RadialMatInst);
        }
    }
    if(RadialMatInst){
        RadialMatInst->SetScalarParameterValue("StartPoint", StartPoint);
        RadialMatInst->SetScalarParameterValue("DegreeInPercent", Radius);
        RadialMatInst->SetScalarParameterValue("InnerRadius", InnerRadius);
        RadialMatInst->SetScalarParameterValue("OuterRadius", OuterRadius);
        RadialMatInst->SetVectorParameterValue("Color",BaseColor);
    }

    
}

void URadialMenuItemWidget::SetStartPointNRadius(float sPoint, float r){
    StartPoint=sPoint;
    Radius=r;
    SynchronizeProperties();
}

void URadialMenuItemWidget::SetSize(FVector2D size){
    if(RadialItemSizeBox){
        RadialItemSizeBox->SetWidthOverride(size.X);
        RadialItemSizeBox->SetHeightOverride(size.Y);

    }
}

void URadialMenuItemWidget::SetItemIconPosition(float dist){
    FVector2D pos(RadialItemSizeBox->WidthOverride/2,RadialItemSizeBox->HeightOverride/2);
    float localAngle=StartPoint+Radius/2.0f;
    localAngle=(localAngle-0.25f)*360.0f;

    FVector2D unitVec;
    FMath::SinCos(&unitVec.Y, &unitVec.X, FMath::DegreesToRadians(localAngle));
    pos+=unitVec*dist;

    UCanvasPanelSlot* slot=Cast<UCanvasPanelSlot>(RItemIcon->Slot);
    if(slot){
        slot->SetPosition(pos);
    }
}
void URadialMenuItemWidget::SetItemIconSize(FVector2D size){
    UCanvasPanelSlot* slot=Cast<UCanvasPanelSlot>(RItemIcon->Slot);
    if(slot){
        slot->SetSize(size);
    } 
}