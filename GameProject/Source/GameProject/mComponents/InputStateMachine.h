// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.h"
#include "InputStateMachine.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuickSlotChanged);

UENUM(BlueprintType)
enum class InputState: uint8{PlayerInput, Building, UI_CraftInv, UI_Dialog, UI_BuildingMenu};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT_API UInputStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputStateMachine();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputState")
	InputState ActState;
	UPROPERTY(BlueprintReadWrite, Category = "InputState")
	InputState BeforeUI;

	int32 EquippedQuickSlot;
	UItemBase* LastEquippedItem;

	void RefreshEquippedItem();

	UFUNCTION()
	void QuickSlot1();
	UFUNCTION()
	void QuickSlot2();
	UFUNCTION()
	void QuickSlot3();
	UFUNCTION()
	void QuickSlot4();
	UFUNCTION()
	void QuickSlot5();
	UFUNCTION()
	void QuickSlot6();

	UFUNCTION()
	void UseEquippedItem();
	UFUNCTION()
	void StopUseEquippedItem();

	void UnequipItem();

	UPROPERTY(BlueprintAssignable, Category="QuickSlots")
	FQuickSlotChanged OnQuickSlotChanged;
};
