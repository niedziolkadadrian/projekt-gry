// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "DialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UDialogWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateComboCount(int32 Value);
	void ResetComboCount();
	void PlayDialogFadeAnim();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* TXTDialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* DialogCanva;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim))
	class UWidgetAnimation* DialogFadeInAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim))
	class UWidgetAnimation* DialogFadeOutAnim;
	
};
