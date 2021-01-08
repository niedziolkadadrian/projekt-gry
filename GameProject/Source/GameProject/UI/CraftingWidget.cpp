// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingWidget.h"

UCraftingWidget::UCraftingWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
    openedType=-1;
    CraftWindowOpened=false;
}

void UCraftingWidget::NativeConstruct(){
    Super::NativeConstruct();
    if(CraftingCanva){
        CraftingCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UCraftingWidget::ShowCrafting(){
    if(CraftingCanva){
        if(CraftingCanva->Visibility == ESlateVisibility::Hidden){
            CraftingCanva->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UCraftingWidget::HideCrafting(){
    if(CraftingCanva){
        CraftingCanva->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UCraftingWidget::Update(UInventoryComponent* Inventory){

}

void UCraftingWidget::SynchronizeProperties(){
    Super::SynchronizeProperties();
	OnSynchronizeProperties();
}

void UCraftingWidget::OnSynchronizeProperties_Implementation(){
    if(TypesBox){
        TypesBox->ClearChildren();
        int ind=0;
        for(int i=0;i<NumOfTypes;i++){
            UCraftingTypeWidget* elem=nullptr;
            if(CraftingTypeClass)
                elem=CreateWidget<UCraftingTypeWidget>(this,CraftingTypeClass);
            if(elem){
                if(TypesBox)
                    TypesBox->AddChildToVerticalBox(elem);
                
                if(i<TypeIcons.Num())
                    if(TypeIcons[i])
                        elem->TypeImage->SetBrushFromTexture(TypeIcons[i],false);
                elem->Index=i;
                elem->OnCraftingTypeClicked.AddDynamic(this, &UCraftingWidget::OnCraftingTypeClick);
                elem->OnCraftingItemClicked.AddDynamic(this, &UCraftingWidget::OnCraftingItemClick);
                //Dodawanie rzeczy do Typu
                elem->CraftingItems->ClearChildren();
                if(i<NumOfItemsInTypes.Num()){
                    for(int j=0;j<NumOfItemsInTypes[i];j++){
                        if(ind<CraftItems.Num()){
                            if(CraftItems[ind]){
                                elem->AddItem(CraftItems[ind],ind);
                                ind++;
                            }
                        }  
                    }
                }
            }
        }
    }
}

void UCraftingWidget::OnCraftingItemClick(int32 index){
    //Zamykanie poprzednich
    if(openedType!=-1){
        if(TypesBox){
            UCraftingTypeWidget* elem=Cast<UCraftingTypeWidget>(TypesBox->GetChildAt(openedType));
            if(elem){
                elem->HideCraftingType();
            }
        }  
    }
    UItemBase* Item=CraftItems[index].GetDefaultObject();//NewObject<UItemBase>(this,CraftItems[index]);
    if(Item){
        CraftWindow->ShowCraftWindow();
        CraftWindow->Update(Item);
        CraftWindowOpened=true;
    }
    openedType=-1;
}

void UCraftingWidget::OnCraftingTypeClick(int32 index){
    
    //Zamykanie poprzednich
    if(openedType!=-1){
        if(TypesBox){
            UCraftingTypeWidget* elem=Cast<UCraftingTypeWidget>(TypesBox->GetChildAt(openedType));
            if(elem){
                elem->HideCraftingType();
            }
        }  
    }
    if(CraftWindowOpened){
        CraftWindow->HideCraftWindow();
        CraftWindowOpened=false;
    }
    //Otwieranie
    UCraftingTypeWidget* typeWidget=Cast<UCraftingTypeWidget>(TypesBox->GetChildAt(index));
    if(typeWidget){
        typeWidget->ShowCraftingType();
        openedType=index;
    }  
}