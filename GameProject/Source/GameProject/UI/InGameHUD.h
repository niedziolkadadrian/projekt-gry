// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"

#include "DialogWidget.h"
#include "HintWidget.h"
#include "InventoryWidget.h"

#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	AInGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float deltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> DialogWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> HintWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	
	UDialogWidget* GetDialogWidget();
	UHintWidget* GetHintWidget();
	UInventoryWidget* GetInventoryWidget();
private:
	UDialogWidget* dialogWidget;
	UHintWidget* hintWidget;
	UInventoryWidget* inventoryWidget;
};
