// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "../MouseSlot.h"
#include "../mComponents/InputStateMachine.h"

#include "DialogWidget.h"
#include "HintWidget.h"
#include "InventoryWidget.h"
#include "PlayerInventoryWidget.h"
#include "CraftingWidget.h"
#include "RadialMenuWidget.h"
#include "QuickSlotsWidget.h"

#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	AInGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float deltaSeconds) override;
	
	int32 ActiveUIElems;
	bool UIControl;
	void ChangeInputType();

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> DialogWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> HintWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> PlayerInventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> CraftingWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> RadialMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> QuickSlotsWidgetClass;
	
	UMouseSlot* GetMouseSlot();
	UDialogWidget* GetDialogWidget();
	UHintWidget* GetHintWidget();
	UInventoryWidget* GetInventoryWidget();
	class UPlayerInventoryWidget* GetPlayerInventoryWidget();
	class UCraftingWidget* GetCraftingWidget();
	URadialMenuWidget* GetRadialMenuWidget();
	UQuickSlotsWidget* GetQuickSlotsWidget();
private:
	UPROPERTY()
	UMouseSlot* mouseSlot;

	UUserWidget* hudWidget;
	UCanvasPanel* hudWidgetCanva;
	UDialogWidget* dialogWidget;
	UHintWidget* hintWidget;
	UInventoryWidget* inventoryWidget;
	class UPlayerInventoryWidget* playerInventoryWidget;
	class UCraftingWidget* craftingWidget;
	URadialMenuWidget* radialMenuWidget;
	UQuickSlotsWidget* quickSlotsWidget;
	
};
