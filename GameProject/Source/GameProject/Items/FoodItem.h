// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "../mComponents/InputStateMachine.h"
#include "../GameProjectCharacter.h"

#include "FoodItem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UFoodItem : public UItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=(ClampMin=0.f))
	float HungerToRecover;

protected:	
	virtual void OnUse_Implementation(class AActor* Character);
	virtual void OnEquip_Implementation(class AActor* Character);
	virtual void OnUnEquip_Implementation(class AActor* Character);
};
