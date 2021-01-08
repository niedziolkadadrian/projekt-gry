// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "../mComponents/InventoryComponent.h"
#include "CraftWindowWidget.h"
#include "CraftingTypeWidget.h"
#include "Components/VerticalBox.h"
#include "../Items/ItemBase.h"
#include "CraftingWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UCraftingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCraftingWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

	void ShowCrafting();
	void HideCrafting();
	void Update(UInventoryComponent* Inventory);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumOfTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> TypeIcons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> NumOfItemsInTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UItemBase>> CraftItems;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* CraftingCanva;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UVerticalBox* TypesBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCraftWindowWidget* CraftWindow;

	UPROPERTY(EditDefaultsOnly, Category="Crafting")
	TSubclassOf<UCraftingTypeWidget> CraftingTypeClass;

	virtual void SynchronizeProperties() override;
	UFUNCTION(BlueprintNativeEvent, Category = "Crafting")
	void OnSynchronizeProperties();
	void OnSynchronizeProperties_Implementation();

	UFUNCTION()
	void OnCraftingItemClick(int32 index);

	UFUNCTION()
	void OnCraftingTypeClick(int32 index);

private:
	int32 openedType;
	bool CraftWindowOpened;
};
