// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryWidget.h"

UPlayerInventoryWidget::UPlayerInventoryWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void UPlayerInventoryWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(PlayerInvCanva){
        PlayerInvCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UPlayerInventoryWidget::ShowInventory(){
    if(PlayerInvCanva){
        if(PlayerInvCanva->Visibility == ESlateVisibility::Hidden){
            PlayerInvCanva->SetVisibility(ESlateVisibility::Visible);
        }
    }
}
void UPlayerInventoryWidget::HideInventory(){
    if(PlayerInvCanva){
        PlayerInvCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UPlayerInventoryWidget::Update(UInventoryComponent* Inventory){
    PlayerInvName->SetText(Inventory->InventoryName);
    QuickActionSlots->ClearChildren();
    InventorySlots->ClearChildren();
    
    for(int i=0;i<Inventory->Size.X;i++){
        if(InventoryItemWidgetClass){
            UInventoryItemWidget* elem=CreateWidget<UInventoryItemWidget>(this,InventoryItemWidgetClass);
            QuickActionSlots->AddChildToUniformGrid(elem, 0, i);
            elem->QuickActionBox->SetVisibility(ESlateVisibility::Visible);
            elem->QuickActionIndex->SetText(FText::FromString(FString::FromInt(i+1)));
            UItemBase* Item=Inventory->Items[0*9+i];
            if(Item){
                if(Item->Icon)
                    elem->ItemImage->SetBrushFromTexture(Item->Icon,true);
                elem->ItemImage->SetVisibility(ESlateVisibility::Visible);
                if(Item->Quantity>1){
                    elem->ItemQuantityBox->SetVisibility(ESlateVisibility::Visible);
                    elem->ItemQuantity->SetText(FText::FromString(FString::FromInt(Item->Quantity)));
                }   
            }
        }
            
    }

    for(int j=1;j<Inventory->Size.Y;j++){
        for(int i=0;i<Inventory->Size.X;i++){
            if(InventoryItemWidgetClass){
                UInventoryItemWidget* elem=CreateWidget<UInventoryItemWidget>(this,InventoryItemWidgetClass);
                InventorySlots->AddChildToUniformGrid(elem, j-1, i);
                UItemBase* Item=Inventory->Items[j*9+i];
                if(Item){
                    if(Item->Icon)
                        elem->ItemImage->SetBrushFromTexture(Item->Icon,true);
                    elem->ItemImage->SetVisibility(ESlateVisibility::Visible);
                    if(Item->Quantity>1){
                        elem->ItemQuantityBox->SetVisibility(ESlateVisibility::Visible);
                        elem->ItemQuantity->SetText(FText::FromString(FString::FromInt(Item->Quantity)));
                    }    
                }
            }
        }
    }

    if(InvWrap){
        FVector2D size=Cast<UCanvasPanelSlot>(InvWrap->Slot)->GetSize();
        size.X+=100;
        size.Y=(size.Y/2)+100;
        size*=-1;
        Cast<UCanvasPanelSlot>(InvWrap->Slot)->SetPosition(size);
    }
}