// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "../mComponents/InventoryComponent.h"
#include "InGameHUD.h"
#include "InventoryItemWidget.h"
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

	UFUNCTION(BlueprintCallable)
	void ShowInventory();
	UFUNCTION(BlueprintCallable)
	void HideInventory();
	UFUNCTION(BlueprintCallable)
	void Update(UInventoryComponent* Inventory);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* InvCanva;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class USizeBox* InvWrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* InvName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UUniformGridPanel* InventorySlots;

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TSubclassOf<UUserWidget> InventoryItemWidgetClass;

	UFUNCTION()
	void OnInvItemClicked(int32 x, int32 y);

private:
	UInventoryComponent* currentInventory;	
};
