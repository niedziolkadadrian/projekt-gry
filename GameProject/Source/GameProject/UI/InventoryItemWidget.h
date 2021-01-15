// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Fonts/SlateFontInfo.h"
#include "InventoryItemWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryItemClicked, int32, x, int32, y);
/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UInventoryItemWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
	FVector2D Size;
	UPROPERTY(EditAnywhere)
	int32 FontSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class USizeBox* WidgetSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* InvItemButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UBorder* ItemImageBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UBorder* ItemQuantityBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UBorder* QuickActionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* ItemQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* QuickActionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint position;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDescription;

	UFUNCTION()
	void OnClick();
	
	void SetSize(FVector2D s);
	void SetFontSize(int32 s);
	virtual void SynchronizeProperties() override;

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FInventoryItemClicked OnInventoryItemClicked;
};
