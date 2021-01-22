// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "ActionCircleWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UActionCircleWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UActionCircleWidget(const FObjectInitializer& ObjectInitializer);
	void NativeConstruct();
	
	UFUNCTION(BlueprintCallable)
	void ShowActionCircle();
	UFUNCTION(BlueprintCallable)
	void HideActionCircle();
	UFUNCTION(BlueprintCallable)
	void Update(float r);

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
	FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UImage* ActionCircle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* ActionCircleCanva;

	virtual void SynchronizeProperties() override;	

private:
	UMaterialInstanceDynamic* RadialMatInst;
	UMaterialInterface* LastRadialMat;
};
