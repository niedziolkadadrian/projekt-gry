// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "../Items/ItemBase.h"
#include "InventoryItemWidget.h"
#include "../mComponents/InventoryComponent.h"
#include "../MouseSlot.h"
#include "InGameHUD.h"
#include "CraftWindowWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UCraftWindowWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UCraftWindowWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	
	void ShowCraftWindow();
	void HideCraftWindow();
	void Update(UItemBase* Item);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	USizeBox* CraftWidgetBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UInventoryItemWidget* CraftItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* IngredientsBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* CraftButton;

	UPROPERTY(EditDefaultsOnly, Category="CraftWindow")
	TSubclassOf<UUserWidget> InventoryItemWidgetClass;

	UFUNCTION()
	void OnCraftClicked();
	
private:
	void RefreshIngredients(class UItemBase* Item);
	
	UPROPERTY()
	class UItemBase* ActualItem;

	bool SufficientResources;
};
