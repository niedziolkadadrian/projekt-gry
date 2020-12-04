// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "../mComponents/InventoryComponent.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void ShowInventory();
	void HideInventory();
	void Update(UInventoryComponent* Inventory);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* InvCanva;
	
};
