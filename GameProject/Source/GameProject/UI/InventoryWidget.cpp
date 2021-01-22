// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void UInventoryWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(InvCanva){
        InvCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UInventoryWidget::ShowInventory(){
    if(InvCanva){
        if(InvCanva->Visibility == ESlateVisibility::Hidden){
            InvCanva->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UInventoryWidget::HideInventory(){
    currentInventory=nullptr;
    if(InvCanva){
        InvCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UInventoryWidget::Update(UInventoryComponent* Inventory){
    currentInventory=Inventory;
    InvName->SetText(Inventory->InventoryName);
    InventorySlots->ClearChildren();

    for(int j=0;j<Inventory->Size.Y;j++){
        for(int i=0;i<Inventory->Size.X;i++){
             if(InventoryItemWidgetClass){
                UInventoryItemWidget* elem=CreateWidget<UInventoryItemWidget>(this,InventoryItemWidgetClass);
                InventorySlots->AddChildToUniformGrid(elem, j, i);
                elem->position=FIntPoint(i,j);
                elem->OnInventoryItemClicked.AddDynamic(this, &UInventoryWidget::OnInvItemClicked);
                UItemBase* Item=Inventory->Items[(j*Inventory->Size.X)+i];
                if(Item){
                    if(Item->Icon)
                        elem->ItemImage->SetBrushFromTexture(Item->Icon,false);
                    elem->ItemImage->SetVisibility(ESlateVisibility::Visible);
                    if(Item->Quantity>1){
                        elem->ItemQuantityBox->SetVisibility(ESlateVisibility::Visible);
                        elem->ItemQuantity->SetText(FText::FromString(FString::FromInt(Item->Quantity)));
                    }
                    elem->ItemName=Item->ItemDisplayName;
                    elem->ItemDescription=Item->ItemDescription;    
                }
            }
        }
    }
}

void UInventoryWidget::OnInvItemClicked(int32 x, int32 y){
    int32 width=currentInventory->Size.X;
    AInGameHUD* InGameHUD=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
    if(InGameHUD){
        if(currentInventory->Items[y*width+x]){
            if(InGameHUD->GetMouseSlot()->isEmpty()){
                UItemBase* pom=currentInventory->Items[y*width+x];
                InGameHUD->GetMouseSlot()->AddItem(pom, InventoryItemWidgetClass);
                currentInventory->RemoveItemFromSlot(y*width+x);
            }
            else{
                UItemBase* pom=InGameHUD->GetMouseSlot()->GetItem();
                InGameHUD->GetMouseSlot()->RemoveItem();
                InGameHUD->GetMouseSlot()->AddItem(currentInventory->Items[y*width+x], InventoryItemWidgetClass);
                if(currentInventory->RemoveItemFromSlot(y*width+x)){
                     currentInventory->AddItemIndx(pom,y*width+x);
                }
            }
        }
        else{
            if(!InGameHUD->GetMouseSlot()->isEmpty()){
                UItemBase* pom=InGameHUD->GetMouseSlot()->GetItem();
                currentInventory->AddItemIndx(pom,y*width+x);
                InGameHUD->GetMouseSlot()->RemoveItem();
            }
        }   
    }
}