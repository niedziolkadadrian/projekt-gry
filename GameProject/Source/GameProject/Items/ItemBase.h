// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class GAMEPROJECT_API UItemBase : public UObject
{
	GENERATED_BODY()
public:
	UItemBase();

	virtual class UWorld* GetWorld() const {return World;};
	
	UPROPERTY(Transient)
	class UWorld* World;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	FText UseText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	class UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	class UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	FText ItemDisplayName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=(MultiLine=true))
	FText ItemDescription;

	//which inventory owns this item (f.e player inv, chest inv, npc inv)
	UPROPERTY()
	class UInventoryComponent* OwningInventory;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void OnUse(class AGameProjectCharacter* Character);
	virtual void OnUse_Implementation(class AGameProjectCharacter* Character) PURE_VIRTUAL(UItemBase, );
	
};
