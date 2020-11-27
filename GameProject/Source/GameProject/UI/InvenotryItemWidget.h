// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "InvenotryItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UInvenotryItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UInvenotryItemWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* InvItemButton;	
};
