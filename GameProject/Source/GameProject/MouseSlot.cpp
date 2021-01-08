// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseSlot.h"


UMouseSlot::UMouseSlot()
{
    Item=nullptr;
}

void UMouseSlot::AddItem(UItemBase* item, TSubclassOf<UUserWidget> MouseItemWidgetClass){
    Item=item;
    APlayerController* PC=GetWorld()->GetFirstPlayerController();
    if(PC){
        PC->CurrentMouseCursor=EMouseCursor::Custom;
        UInventoryItemWidget* itemWidget=CreateWidget<UInventoryItemWidget>(GetWorld(), MouseItemWidgetClass);
        PC->SetMouseCursorWidget(EMouseCursor::Custom,itemWidget);
        if(itemWidget){
            itemWidget->InvItemButton->SetRenderScale(FVector2D(0.5,0.5));
            if(item->Icon)
                itemWidget->ItemImage->SetBrushFromTexture(item->Icon,true);
            itemWidget->ItemImage->SetVisibility(ESlateVisibility::Visible);
            if(item->Quantity>1){
                itemWidget->ItemQuantityBox->SetVisibility(ESlateVisibility::Visible);
                itemWidget->ItemQuantity->SetText(FText::FromString(FString::FromInt(item->Quantity)));
            }
        }
        PC->bShowMouseCursor=false;
        PC->SetInputMode(FInputModeGameOnly());
        PC->SetInputMode(FInputModeGameAndUI());
        PC->bShowMouseCursor=true;
    }
}

void UMouseSlot::RemoveItem(){
    Item=nullptr;
    APlayerController* PC=GetWorld()->GetFirstPlayerController();
    if(PC){
        PC->CurrentMouseCursor=EMouseCursor::Default;
        PC->bShowMouseCursor=false;
        PC->SetInputMode(FInputModeGameOnly());
        PC->SetInputMode(FInputModeGameAndUI());
        PC->bShowMouseCursor=true;
    }
}

UItemBase* UMouseSlot::GetItem(){
    return Item;
}

bool UMouseSlot::isEmpty(){
    if(Item)
        return false;
    return true;
}

void UMouseSlot::DropItem(){
    if(Item){
        GetWorld()->GetFirstPlayerController()->CurrentMouseCursor=EMouseCursor::Default;
        //spawning pickable item
        FVector loc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
        FVector przes=GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorForwardVector();
        loc+=przes*100;
        APickableItem* pickItem= GetWorld()->SpawnActor<APickableItem>(loc,FRotator(0,0,0),FActorSpawnParameters());
        pickItem->SetItem(Item->GetClass(),Item);
        pickItem->Mesh->SetSimulatePhysics(true); 
        RemoveItem(); //remove from mouse slot     
    }
}
