// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Items/ItemBase.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	bool AddItem(class UItemBase* Item);
	bool AddItem(class UItemBase* Item, int32 Index);
	bool RemoveItems(class UItemBase* Item, int32 Quantity);
	bool RemoveItemFromSlot(int32 Index);

	int32 GetItemQuantity(class UItemBase* Item);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Items")
	TArray<class UItemBase*> Items;

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	FIntPoint Size;

	UPROPERTY(EditAnywhere, Category="Inventory")
	FText InventoryName;

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FInventoryUpdated OnInventoryUpdated;
		
};
