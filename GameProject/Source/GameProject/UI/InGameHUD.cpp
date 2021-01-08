// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"

AInGameHUD::AInGameHUD(){
    ActiveUIElems=0;
    UIControl=false;
}

void AInGameHUD::BeginPlay(){
    Super::BeginPlay();
    mouseSlot=NewObject<UMouseSlot>(GetWorld());
    if(HUDWidgetClass){
        hudWidget = CreateWidget<UUserWidget>(GetWorld(),HUDWidgetClass);
        if(hudWidget){
            hudWidget->AddToViewport();
            hudWidgetCanva=Cast<UCanvasPanel>(hudWidget->GetRootWidget());
        }
    }
    if(DialogWidgetClass){
        dialogWidget = CreateWidget<UDialogWidget>(hudWidget,DialogWidgetClass);
        if(dialogWidget){
            hudWidgetCanva->AddChildToCanvas(dialogWidget);
        }
    }
    if(HintWidgetClass){
        hintWidget = CreateWidget<UHintWidget>(hudWidget,HintWidgetClass);
        if(hintWidget){
            hudWidgetCanva->AddChildToCanvas(hintWidget);
        }
    }
    if(InventoryWidgetClass){
        inventoryWidget = CreateWidget<UInventoryWidget>(hudWidget,InventoryWidgetClass);
        if(inventoryWidget){
            hudWidgetCanva->AddChildToCanvas(inventoryWidget);
        }
    }
    if(PlayerInventoryWidgetClass){
        playerInventoryWidget = CreateWidget<UPlayerInventoryWidget>(hudWidget,PlayerInventoryWidgetClass);
        if(playerInventoryWidget){
            hudWidgetCanva->AddChildToCanvas(playerInventoryWidget);
        }
    }
    if(CraftingWidgetClass){
        craftingWidget = CreateWidget<UCraftingWidget>(hudWidget,CraftingWidgetClass);
        if(craftingWidget){
            hudWidgetCanva->AddChildToCanvas(craftingWidget);
        }
    }
    if(RadialMenuWidgetClass){
        radialMenuWidget = CreateWidget<URadialMenuWidget>(hudWidget,RadialMenuWidgetClass);
        if(radialMenuWidget){
            hudWidgetCanva->AddChildToCanvas(radialMenuWidget);
        }
    }
}

void AInGameHUD::Tick(float deltaSeconds){
    Super::Tick(deltaSeconds);
}

void AInGameHUD::DrawHUD(){
    Super::DrawHUD();
}

void AInGameHUD::ChangeInputType(){
	if(!UIControl){
		if(ActiveUIElems>0){
			APlayerController* PC=GetWorld()->GetFirstPlayerController();
			if(PC){
                PC->SetInputMode(FInputModeGameAndUI());
                PC->bShowMouseCursor = true;
				PC->bEnableClickEvents = true;
				PC->bEnableMouseOverEvents = true;
            }
            UIControl=true;
		}
	}
	else if(!ActiveUIElems){
		APlayerController* PC=GetWorld()->GetFirstPlayerController();
		if(PC){
            PC->SetInputMode(FInputModeGameOnly());
            PC->bShowMouseCursor = false;
			PC->bEnableClickEvents = false;
			PC->bEnableMouseOverEvents = false;
                
            //Zmiana sterowania z UI na poprzednie
            AActor* Actor=Cast<AActor>(PC->GetPawn());
            if(Actor){
                UInputStateMachine* InputStateMachine=Actor->FindComponentByClass<UInputStateMachine>();
                if(InputStateMachine)
                    InputStateMachine->ActState=InputStateMachine->BeforeUI;
            }
        }
        UIControl=false;
	}
}

UMouseSlot* AInGameHUD::GetMouseSlot(){
    return mouseSlot;
}

UDialogWidget* AInGameHUD::GetDialogWidget(){
    if(dialogWidget)
        return dialogWidget;
    return nullptr;
}

UHintWidget* AInGameHUD::GetHintWidget(){
    if(hintWidget)
        return hintWidget;
    return nullptr;
}

UInventoryWidget* AInGameHUD::GetInventoryWidget(){
     if(inventoryWidget)
        return inventoryWidget;
    return nullptr;
}

UPlayerInventoryWidget* AInGameHUD::GetPlayerInventoryWidget(){
    if(playerInventoryWidget)
        return playerInventoryWidget;
    return nullptr;
}

UCraftingWidget* AInGameHUD::GetCraftingWidget(){
    if(craftingWidget)
        return craftingWidget;
    return nullptr;
}

URadialMenuWidget* AInGameHUD::GetRadialMenuWidget(){
    if(radialMenuWidget)
        return radialMenuWidget;
    return nullptr;
}

