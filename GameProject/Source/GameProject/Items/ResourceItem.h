// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "ResourceItem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UResourceItem : public UItemBase
{
	GENERATED_BODY()
public:
	UResourceItem();

protected:	
	virtual void OnUse_Implementation(class AActor* Character);
	virtual void OnEquip_Implementation(class AActor* Character);
	virtual void OnUnEquip_Implementation(class AActor* Character);	
	virtual void OnStopUse_Implementation(class AActor* Character);
	
};
