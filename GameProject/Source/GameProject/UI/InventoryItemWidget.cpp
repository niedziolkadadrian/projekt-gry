// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemWidget.h"

UInventoryItemWidget::UInventoryItemWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
    position=FIntPoint(0,0);
    Size=FVector2D(64.0f,64.0f);
    FontSize=12;
    ItemName=FText::FromString("");
    ItemDescription=FText::FromString("");
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
    if(InvItemButton){
        InvItemButton->OnClicked.AddDynamic(this, &UInventoryItemWidget::OnClick);
    }
}
void UInventoryItemWidget::SetSize(FVector2D s){
    Size=s;
    SynchronizeProperties();
}

void UInventoryItemWidget::SetFontSize(int32 s){
    FontSize=s;
    SynchronizeProperties();
}

void UInventoryItemWidget::SynchronizeProperties(){
    Super::SynchronizeProperties();
    if(WidgetSizeBox){
        WidgetSizeBox->SetHeightOverride(Size.Y);
        WidgetSizeBox->SetWidthOverride(Size.X);
    }
    
    FSlateFontInfo font;
    if(ItemQuantity)
        font=ItemQuantity->Font;
    font.Size=FontSize;

    if(ItemQuantity){
        ItemQuantity->SetFont(font);
    }
    if(QuickActionIndex){
        QuickActionIndex->SetFont(font);
    }


    
}

void UInventoryItemWidget::OnClick(){
    OnInventoryItemClicked.Broadcast(position.X, position.Y);
}
