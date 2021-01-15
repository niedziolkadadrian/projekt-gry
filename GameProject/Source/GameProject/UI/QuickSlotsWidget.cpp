// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotsWidget.h"

UQuickSlotsWidget::UQuickSlotsWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
    
}

void UQuickSlotsWidget::NativeConstruct(){
    Super::NativeConstruct();
    Update();
}

void UQuickSlotsWidget::ShowQuickSlots(){
    if(QuickSlotsCanva){
        if(QuickSlotsCanva->Visibility == ESlateVisibility::Hidden){
            QuickSlotsCanva->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UQuickSlotsWidget::HideQuickSlots(){
    if(QuickSlotsCanva){
        QuickSlotsCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UQuickSlotsWidget::Update(){
    AActor* Player=Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if(Player){
        UInventoryComponent* Inventory=Player->FindComponentByClass<UInventoryComponent>();
        UInputStateMachine* InputStateMachine=Player->FindComponentByClass<UInputStateMachine>();
        if(Inventory && InputStateMachine){
            if(SelectedBox && ItemsBox){
                SelectedBox->ClearChildren();
                ItemsBox->ClearChildren();
                for(int i=0;i<Inventory->Size.X;i++){
                    UInventoryItemWidget* elem=CreateWidget<UInventoryItemWidget>(this,InventoryItemWidgetClass);
                    UImage* border=WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
                    if(elem){
                        UHorizontalBoxSlot* slot=ItemsBox->AddChildToHorizontalBox(elem);
                        if(slot)
                            slot->SetPadding(FMargin(4.0f));
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
                    if(border){
                        SelectedBox->AddChildToHorizontalBox(border);
                        border->SetBrushSize(FVector2D(72.0f,72.0f));
                        border->SetColorAndOpacity(FLinearColor(0.864583f,0.565199f,0.036024f,0.8f));
                        if(i!=InputStateMachine->EquippedQuickSlot)
                            border->SetVisibility(ESlateVisibility::Hidden);
                    }
                }
            }
        }
    }
}