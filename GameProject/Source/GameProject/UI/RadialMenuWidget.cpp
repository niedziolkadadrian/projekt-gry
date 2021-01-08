// Fill out your copyright notice in the Description page of Project Settings.


#include "RadialMenuWidget.h"

URadialMenuWidget::URadialMenuWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
    NumOfElems=2;
    gapSize=.004f;
    iconSize=FVector2D(32.0f,32.0f);
    iconDistance=50.0f;
}

void URadialMenuWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(RadialMenuCanva){
        RadialMenuCanva->SetVisibility(ESlateVisibility::Hidden);
    }
    if(SelectButton){
        SelectButton->OnPressed.AddDynamic(this, &URadialMenuWidget::OnClickedItem);  
    }
}

void URadialMenuWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime){
    Super::NativeTick(MyGeometry, InDeltaTime);
    for(int i=0;i<NumOfElems;i++){
        URadialMenuItemWidget* item=Cast<URadialMenuItemWidget>(ItemsOverlay->GetChildAt(i));
        if(item)
            item->isSelected();
    }
}

void URadialMenuWidget::ShowRadialMenu(){
    if(RadialMenuCanva){
        if(RadialMenuCanva->Visibility == ESlateVisibility::Hidden){
            RadialMenuCanva->SetVisibility(ESlateVisibility::Visible);
        }
    }
    if(GEngine)
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), ItemsOverlay->GetChildrenCount()));
}

void URadialMenuWidget::HideRadialMenu(){
    if(RadialMenuCanva){
        RadialMenuCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void URadialMenuWidget::SynchronizeProperties(){
    Super::SynchronizeProperties();
	OnSynchronizeProperties();
}

void URadialMenuWidget::OnSynchronizeProperties_Implementation(){
    if(NumOfElems){
        if(ItemsOverlay && RadialMenuItemWidgetClass){
            ItemsOverlay->ClearChildren();
            float radius=1.0f/(float)NumOfElems;
            float sPosition=0.5f-radius/2+gapSize/2;
            for(int i=0;i<NumOfElems;i++){
                URadialMenuItemWidget* elem=CreateWidget<URadialMenuItemWidget>(this,RadialMenuItemWidgetClass);
                ItemsOverlay->AddChildToOverlay(elem);
                elem->SetStartPointNRadius(sPosition, radius-gapSize);
                elem->SetSize(Cast<UCanvasPanelSlot>(ItemsOverlay->Slot)->GetSize());
                elem->SetItemIconPosition(iconDistance);
                elem->SetItemIconSize(iconSize);
                sPosition+=radius;
                if(sPosition>1.0f)
                    sPosition-=1.0f;
            }
        }
    }
}

void URadialMenuWidget::SetElemIcon(int i, UTexture2D* icon){
    if(ItemsOverlay){
        URadialMenuItemWidget* item=Cast<URadialMenuItemWidget>(ItemsOverlay->GetChildAt(i));
        if(item){
            item->RItemIcon->SetBrushFromTexture(icon, false);
            item->RItemIcon->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void URadialMenuWidget::SetNumOfElems(int i){
    if(i<=0)
        i=1;
    NumOfElems=i;
    SynchronizeProperties();
}

void URadialMenuWidget::OnClickedItem(){
    int32 selectedItem=-1;
    for(int32 i=0;i<NumOfElems;i++){
        URadialMenuItemWidget* item=Cast<URadialMenuItemWidget>(ItemsOverlay->GetChildAt(i));
        if(item){
            if(item->isSelected()){
                selectedItem=i;
                break;
            }
        }   
    }
    if(GEngine)
      	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Wybrano %d"),selectedItem));
    
    OnRadialItemClicked.Broadcast(selectedItem);
}