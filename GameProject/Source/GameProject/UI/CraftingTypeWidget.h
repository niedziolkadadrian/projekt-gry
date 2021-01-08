// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "InventoryItemWidget.h"
#include "../Items/ItemBase.h"
#include "CraftingTypeWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCraftingItemClicked, int32, index);
/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UCraftingTypeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UCraftingTypeWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void ShowCraftingType();
	void HideCraftingType();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* CraftingTypeCanva;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* TypeButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* TypeImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* CraftingItems;

	UPROPERTY(EditDefaultsOnly, Category="CraftingType")
	TSubclassOf<UUserWidget> InventoryItemWidgetClass;

	void AddItem(TSubclassOf<UItemBase> ItemClass, int32 index);

	UFUNCTION()
	void OnItemClicked(int32 x, int32 y);
	
	UFUNCTION()
	void OnTypeClicked();

	UPROPERTY(BlueprintAssignable, Category="Crafting")
	FCraftingItemClicked OnCraftingItemClicked;

	UPROPERTY(BlueprintAssignable, Category="Crafting")
	FCraftingItemClicked OnCraftingTypeClicked;
};
