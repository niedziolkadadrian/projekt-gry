// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Math/Color.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanelSlot.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Math/Vector2D.h"
#include "Math/UnrealMathUtility.h"

#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "RadialMenuItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API URadialMenuItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URadialMenuItemWidget(const FObjectInitializer& ObjectInitializer);
	void NativeConstruct();
	
	//percent of 360*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InnerRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OuterRadius;

	UPROPERTY(EditAnywhere)
    UMaterialInterface* RadialMat;
	UPROPERTY(EditAnywhere)
	FColor BaseColor;
	UPROPERTY(EditAnywhere)
	FColor SelectedColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UImage* RadialImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class USizeBox* RadialItemSizeBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UImage* RItemIcon;
	

	UFUNCTION(BlueprintCallable, Category="RadialMenuItem")
	bool isSelected();

	virtual void SynchronizeProperties() override;
	UFUNCTION(BlueprintNativeEvent, Category = "RadialMenuItem")
	void OnSynchronizeProperties();
	void OnSynchronizeProperties_Implementation();

	void SetStartPointNRadius(float sPoint, float r);
	void SetSize(FVector2D size);
	
	void SetItemIcon(UTexture2D* icon);
	void SetItemIconPosition(float dist);
	void SetItemIconSize(FVector2D size);
private:
	UMaterialInstanceDynamic* RadialMatInst;
	UMaterialInterface* LastRadialMat;
};
