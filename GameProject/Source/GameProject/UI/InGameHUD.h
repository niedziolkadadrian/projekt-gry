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
#include "ActionCircleWidget.h"

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
	
	UPROPERTY(BlueprintReadWrite, Category="Widgets")
	int32 ActiveUIElems;

	bool UIControl;
	UFUNCTION(BlueprintCallable)
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
	
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> ActionCircleWidgetClass;
	
	UFUNCTION(BlueprintCallable)
	UMouseSlot* GetMouseSlot();
	UFUNCTION(BlueprintCallable)
	UDialogWidget* GetDialogWidget();
	UFUNCTION(BlueprintCallable)
	UHintWidget* GetHintWidget();
	UFUNCTION(BlueprintCallable)
	class UInventoryWidget* GetInventoryWidget();
	UFUNCTION(BlueprintCallable)
	class UPlayerInventoryWidget* GetPlayerInventoryWidget();
	UFUNCTION(BlueprintCallable)
	class UCraftingWidget* GetCraftingWidget();
	UFUNCTION(BlueprintCallable)
	URadialMenuWidget* GetRadialMenuWidget();
	UFUNCTION(BlueprintCallable)
	UQuickSlotsWidget* GetQuickSlotsWidget();
	UFUNCTION(BlueprintCallable)
	UActionCircleWidget* GetActionCircleWidget();
private:
	UPROPERTY()
	UMouseSlot* mouseSlot;

	UUserWidget* hudWidget;
	UCanvasPanel* hudWidgetCanva;
	UDialogWidget* dialogWidget;
	UHintWidget* hintWidget;
	class UInventoryWidget* inventoryWidget;
	class UPlayerInventoryWidget* playerInventoryWidget;
	class UCraftingWidget* craftingWidget;
	URadialMenuWidget* radialMenuWidget;
	UQuickSlotsWidget* quickSlotsWidget;
	UActionCircleWidget* actionCircleWidget;
	
};
