// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "HintWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UHintWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UHintWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void ShowHint(FText Value);
	void HideHint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* HintCanva;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* TXTHint;
	
};
