// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RadialMenuItemWidget.h"
#include "Components/Overlay.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "RadialMenuWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRadialItemClicked, int32, index);
/**
 * 
 */
UCLASS()
class GAMEPROJECT_API URadialMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URadialMenuWidget(const FObjectInitializer& ObjectInitializer);
	void NativeConstruct();
	virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;
	void ShowRadialMenu();
	void HideRadialMenu();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* RadialMenuCanva;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* SelectButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UOverlay* ItemsOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
	int32 NumOfElems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float gapSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float iconDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	FVector2D iconSize;
	
	UPROPERTY(EditAnywhere, Category="RadialMenu")
	TSubclassOf<URadialMenuItemWidget> RadialMenuItemWidgetClass;

	virtual void SynchronizeProperties() override;
	UFUNCTION(BlueprintNativeEvent, Category = "RadialMenu")
	void OnSynchronizeProperties();
	void OnSynchronizeProperties_Implementation();

	void SetNumOfElems(int i);
	void SetElemIcon(int i, UTexture2D* icon);

	UFUNCTION()
	void OnClickedItem();

	UPROPERTY(BlueprintAssignable, Category="RadialMenu")
	FRadialItemClicked OnRadialItemClicked;
	
};
