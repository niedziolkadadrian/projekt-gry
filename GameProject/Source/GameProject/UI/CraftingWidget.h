// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "../mComponents/InventoryComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* CraftingCanva;
};
