// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "../Interfaces/InteractInterface.h"
#include "ItemBase.h"
#include "../mComponents/InventoryComponent.h"
#include "PickableItem.generated.h"

UCLASS()
class GAMEPROJECT_API APickableItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, Category="Item")
	TSubclassOf<UItemBase> ItemClass;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category="Item")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category="Item")
	USphereComponent* InteractionZone;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void StartFocus();
	virtual void StartFocus_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void EndFocus();
	virtual void EndFocus_Implementation();

	UFUNCTION(BluePrintCallable, Category="Item")
	void SetItem(TSubclassOf<UItemBase> itmClass,UItemBase* itm);
private:
	UPROPERTY()
	UItemBase* Item;
	bool ToDestroy;

};
