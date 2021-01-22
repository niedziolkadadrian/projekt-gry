// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/ItemBase.h"
#include "BuldingPreview.generated.h"

UCLASS()
class GAMEPROJECT_API ABuldingPreview : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuldingPreview();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category="BuildingPreview")
	bool canBePlaced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BuildingPreview")
	TArray<TSubclassOf<UItemBase>> BuildResources;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BuildingPreview")
	TArray<int32> BuildResourcesQuantity;

};
