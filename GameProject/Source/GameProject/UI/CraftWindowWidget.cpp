// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftWindowWidget.h"

UCraftWindowWidget::UCraftWindowWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
    SufficientResources=false;
}

void UCraftWindowWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(CraftWidgetBox){
        CraftWidgetBox->SetVisibility(ESlateVisibility::Hidden);
    }
    if(CraftButton){
        CraftButton->OnClicked.AddDynamic(this, &UCraftWindowWidget::OnCraftClicked);
    }
}

void UCraftWindowWidget::ShowCraftWindow(){
    if(CraftWidgetBox){
        if(CraftWidgetBox->Visibility == ESlateVisibility::Hidden){
            CraftWidgetBox->SetVisibility(ESlateVisibility::Visible);
        }
    }
}
void UCraftWindowWidget::HideCraftWindow(){
     if(CraftWidgetBox){
        CraftWidgetBox->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UCraftWindowWidget::Update(UItemBase* Item){
    ActualItem=Item;
    if(CraftItem){
        if(Item->Icon)
            CraftItem->ItemImage->SetBrushFromTexture(Item->Icon,false);
        CraftItem->ItemImage->SetVisibility(ESlateVisibility::Visible);
    }
    
    if(IngredientsBox)
        IngredientsBox->ClearChildren();

    for(int i=0;i<Item->CraftIngredients.Num();i++){
        UInventoryItemWidget* elem=nullptr;
        if(InventoryItemWidgetClass)
            elem=CreateWidget<UInventoryItemWidget>(this,InventoryItemWidgetClass);
        
        if(elem){
            if(IngredientsBox)
                IngredientsBox->AddChildToHorizontalBox(elem);

            UItemBase* Ingredient=Item->CraftIngredients[i].GetDefaultObject();
            if(Ingredient)
                if(Ingredient->Icon)
                    elem->ItemImage->SetBrushFromTexture(Ingredient->Icon,false);
            elem->ItemImage->SetVisibility(ESlateVisibility::Visible);
            elem->SetSize(FVector2D(32.0f,32.0f));
        }
    }
    RefreshIngredients(ActualItem);
}

void UCraftWindowWidget::RefreshIngredients(UItemBase* Item){
    AActor* Player=Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
    UInventoryComponent* PlayerInventory=nullptr;
    bool sufRes=true;
    if(Player)
        PlayerInventory=Player->FindComponentByClass<UInventoryComponent>();
    if(PlayerInventory){
        for(int i=0;i<Item->CraftIngredients.Num();i++){
            UInventoryItemWidget* elem=nullptr;
            if(IngredientsBox)
                elem=Cast<UInventoryItemWidget>(IngredientsBox->GetChildAt(i));
            
            if(elem){
                if(i<Item->CraftIngredientsQuantity.Num() && i<Item->CraftIngredients.Num()){
                    UItemBase* Ingredient=Item->CraftIngredients[i].GetDefaultObject();
                    if(Ingredient){
                        if(GEngine)
                            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Liczba jablek %d"),PlayerInventory->GetItemQuantity(Ingredient)));
                        
                        if(PlayerInventory->GetItemQuantity(Ingredient)>=Item->CraftIngredientsQuantity[i]){
                            elem->ItemImageBorder->SetBrushColor(FLinearColor(.0f,1.0f,.0f,.8f));
                        }
                        else{
                            elem->ItemImageBorder->SetBrushColor(FLinearColor(1.0f,.0f,.0f,.8f));
                            sufRes=false;
                        }
                    }
                }
            }
        }
    }
    SufficientResources=sufRes;
}

void UCraftWindowWidget::OnCraftClicked(){
    if(GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("CraftButton")));
        
    if(ActualItem){
        if(SufficientResources){
            AActor* Player=Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
            UInventoryComponent* PlayerInventory=nullptr;
            if(Player)
                PlayerInventory=Player->FindComponentByClass<UInventoryComponent>();
            
            if(PlayerInventory){
                for(int i=0;i<ActualItem->CraftIngredients.Num();i++){
                    UInventoryItemWidget* elem=nullptr;
                    if(IngredientsBox)
                        elem=Cast<UInventoryItemWidget>(IngredientsBox->GetChildAt(i));
                    
                    if(elem){
                        if(i<ActualItem->CraftIngredientsQuantity.Num() && i<ActualItem->CraftIngredients.Num()){
                            UItemBase* Ingredient=ActualItem->CraftIngredients[i].GetDefaultObject();
                            if(Ingredient){
                                PlayerInventory->RemoveItems(Ingredient,ActualItem->CraftIngredientsQuantity[i]);
                            }
                        }
                    }
                }
                UItemBase* Item=NewObject<UItemBase>(GetWorld(),ActualItem->GetClass());
                if(!PlayerInventory->AddItem(Item)){
                    UMouseSlot* slot=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->GetMouseSlot();
                    if(slot){
                        if(!slot->isEmpty())
                            slot->DropItem();
                        
                        slot->AddItem(Item, InventoryItemWidgetClass);
                    }
                }
            }
            
            if(GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Crafted")));
        }
        else{
            if(GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("NotCrafted")));
        }
        RefreshIngredients(ActualItem);
    }
}