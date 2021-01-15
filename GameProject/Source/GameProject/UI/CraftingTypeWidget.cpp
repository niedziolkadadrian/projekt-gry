// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingTypeWidget.h"

UCraftingTypeWidget::UCraftingTypeWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
    Index=-1;
}

void UCraftingTypeWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(CraftingItems){
        CraftingItems->SetVisibility(ESlateVisibility::Hidden);
    }
    if(TypeButton){
        TypeButton->OnClicked.AddDynamic(this, &UCraftingTypeWidget::OnTypeClicked);
    }
}

void UCraftingTypeWidget::ShowCraftingType(){
    if(CraftingItems){
        if(CraftingItems->Visibility == ESlateVisibility::Hidden){
            CraftingItems->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UCraftingTypeWidget::HideCraftingType(){
    if(CraftingItems){
        CraftingItems->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UCraftingTypeWidget::AddItem(TSubclassOf<UItemBase> ItemClass, int32 index){
    if(CraftingItems){
        UInventoryItemWidget* elem=nullptr;
        if(InventoryItemWidgetClass)
            elem=CreateWidget<UInventoryItemWidget>(this,InventoryItemWidgetClass);
        
        if(elem){
            CraftingItems->AddChildToHorizontalBox(elem);
            
            elem->position=FIntPoint(index,0);
            elem->OnInventoryItemClicked.AddDynamic(this,&UCraftingTypeWidget::OnItemClicked);
            
            UItemBase* Item=ItemClass.GetDefaultObject();//NewObject<UItemBase>(this,ItemClass);
            if(Item){
                if(Item->Icon)
                    elem->ItemImage->SetBrushFromTexture(Item->Icon,false);
                elem->ItemName=Item->ItemDisplayName;
                elem->ItemDescription=Item->ItemDescription;
            }
                
            elem->ItemImage->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UCraftingTypeWidget::OnItemClicked(int32 x, int32 y){
    OnCraftingItemClicked.Broadcast(x);
}

void UCraftingTypeWidget::OnTypeClicked(){
    if(GEngine)
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("TypeClicked")));

    OnCraftingTypeClicked.Broadcast(Index);
}