// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UWeaponItem : public UItemBase
{
	GENERATED_BODY()

public:
	UWeaponItem();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=(ClampMin=0.f))
	float AttackDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=(ClampMin=0.f))
	int32 NumberOfUses;

protected:	
	virtual void OnUse_Implementation(class AActor* Character);
	virtual void OnEquip_Implementation(class AActor* Character);
	virtual void OnUnEquip_Implementation(class AActor* Character);	
};
