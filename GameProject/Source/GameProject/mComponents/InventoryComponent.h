// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Items/ItemBase.h"
#include "InputStateMachine.h"
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

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddItem(class UItemBase* Item);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddItemIndx(class UItemBase* Item, int32 Index);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool RemoveItem(class UItemBase* Item);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool RemoveItems(class UItemBase* Item, int32 Quantity);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool RemoveItemFromSlot(int32 Index);

	UFUNCTION(BlueprintCallable, Category="Inventory")
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
