// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponItem.h"
#include "../mComponents/BuildingSystemComponent.h"
#include "BuildingItem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UBuildingItem : public UWeaponItem
{
	GENERATED_BODY()

protected:	
	virtual void OnUse_Implementation(class AActor* Character) override;
	virtual void OnEquip_Implementation(class AActor* Character) override;
	virtual void OnUnEquip_Implementation(class AActor* Character) override;
	virtual void OnStopUse_Implementation(class AActor* Character) override;
};
