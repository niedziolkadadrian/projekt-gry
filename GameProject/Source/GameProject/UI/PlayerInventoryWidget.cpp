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
        UButton* elem=WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
        QuickActionSlots->AddChildToUniformGrid(elem, 0, i);
    }

    for(int j=1;j<Inventory->Size.Y;j++){
        for(int i=0;i<Inventory->Size.X;i++){
            UButton* elem=WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
            InventorySlots->AddChildToUniformGrid(elem, j-1, i);
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