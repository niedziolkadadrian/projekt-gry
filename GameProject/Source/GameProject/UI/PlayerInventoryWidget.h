// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "../mComponents/InventoryComponent.h"
#include "InGameHUD.h"
#include "InventoryItemWidget.h"
#include "../Items/PickableItem.h"
#include "PlayerInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UPlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerInventoryWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void ShowInventory();
	void HideInventory();
	void Update(UInventoryComponent* Inventory);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* PlayerInvCanva;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class USizeBox* InvWrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* PlayerInvName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UUniformGridPanel* InventorySlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UUniformGridPanel* QuickActionSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* ThrowButton;

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TSubclassOf<UUserWidget> InventoryItemWidgetClass;

	UFUNCTION()
	void OnInvItemClicked(int32 x, int32 y);

	UFUNCTION()
	void OnThrowClicked();
private:
	UInventoryComponent* currentInventory;

};
