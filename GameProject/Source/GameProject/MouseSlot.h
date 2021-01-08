// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "UI/InventoryItemWidget.h"
#include "Items/ItemBase.h"
#include "Items/PickableItem.h"
#include "MouseSlot.generated.h"
/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UMouseSlot : public UObject
{
	GENERATED_BODY()
public:
	UMouseSlot();
	
	void AddItem(UItemBase* Item, TSubclassOf<UUserWidget> MouseItemWidgetClass);
	UItemBase* GetItem();
	void RemoveItem();
	bool isEmpty();
	void DropItem();
private:
	UPROPERTY()
	UItemBase* Item;

};
