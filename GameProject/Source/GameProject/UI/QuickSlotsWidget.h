// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "../mComponents/InventoryComponent.h"
#include "../mComponents/InputStateMachine.h"
#include "InventoryItemWidget.h"
#include "Blueprint/WidgetTree.h"
#include "QuickSlotsWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UQuickSlotsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UQuickSlotsWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ShowQuickSlots();
	UFUNCTION(BlueprintCallable)
	void HideQuickSlots();
	UFUNCTION(BlueprintCallable)
	void Update();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* QuickSlotsCanva;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* SelectedBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* ItemsBox;

	UPROPERTY(EditDefaultsOnly, Category="CraftingType")
	TSubclassOf<UUserWidget> InventoryItemWidgetClass;
};
