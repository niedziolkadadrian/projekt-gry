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
    if(ThrowButton){
        ThrowButton->OnClicked.AddDynamic(this, &UPlayerInventoryWidget::OnThrowClicked);  
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
    currentInventory=nullptr;
    if(PlayerInvCanva){
        PlayerInvCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UPlayerInventoryWidget::Update(UInventoryComponent* Inventory){
    currentInventory=Inventory;
    PlayerInvName->SetText(Inventory->InventoryName);
    QuickActionSlots->ClearChildren();
    InventorySlots->ClearChildren();
    
    //QuickActionSlots
    for(int i=0;i<Inventory->Size.X;i++){
        if(InventoryItemWidgetClass){
            UInventoryItemWidget* elem=CreateWidget<UInventoryItemWidget>(this,InventoryItemWidgetClass);
            QuickActionSlots->AddChildToUniformGrid(elem, 0, i);
            elem->position=FIntPoint(i,0);
            elem->OnInventoryItemClicked.AddDynamic(this, &UPlayerInventoryWidget::OnInvItemClicked);
            elem->QuickActionBox->SetVisibility(ESlateVisibility::Visible);
            elem->QuickActionIndex->SetText(FText::FromString(FString::FromInt(i+1)));
            UItemBase* Item=Inventory->Items[i];
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

    //InventorySlots
    for(int j=1;j<Inventory->Size.Y;j++){
        for(int i=0;i<Inventory->Size.X;i++){
            if(InventoryItemWidgetClass){
                UInventoryItemWidget* elem=CreateWidget<UInventoryItemWidget>(this,InventoryItemWidgetClass);
                InventorySlots->AddChildToUniformGrid(elem, j-1, i);
                elem->position=FIntPoint(i,j);
                elem->OnInventoryItemClicked.AddDynamic(this, &UPlayerInventoryWidget::OnInvItemClicked);
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

    /*if(InvWrap){
        int32 posX;
        int32 posY;
        GetWorld()->GetWorld()->GetFirstPlayerController()->GetViewportSize(posX,posY);
        FVector2D pos((float)posX,(float)posY);
        pos/=2;
        Cast<UCanvasPanelSlot>(InvWrap->Slot)->SetPosition(pos);
    }*/
}

void UPlayerInventoryWidget::OnInvItemClicked(int32 x, int32 y){
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
                     currentInventory->AddItem(pom,y*width+x);
                }
            }
            if(GEngine)
		    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "kliknieto");
        }
        else{
            if(!InGameHUD->GetMouseSlot()->isEmpty()){
                UItemBase* pom=InGameHUD->GetMouseSlot()->GetItem();
                currentInventory->AddItem(pom,y*width+x);
                InGameHUD->GetMouseSlot()->RemoveItem();
            }
        }   
    }

    if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Kliknieto %d, %d"),x,y));
}

void UPlayerInventoryWidget::OnThrowClicked(){
    AInGameHUD* InGameHUD=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
    if(InGameHUD){
        InGameHUD->GetMouseSlot()->DropItem();
        
    }
}