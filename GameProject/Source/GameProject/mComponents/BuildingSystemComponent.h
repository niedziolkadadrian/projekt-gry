// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../UI/InGameHUD.h"
#include "InputStateMachine.h"
#include "BuildingSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT_API UBuildingSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UInputStateMachine* InputStateMachine;
	AInGameHUD* InGameHUD;

	int Class;
	bool RadialInputInitialized;
	TArray<int32> StartIndex;

	FTimerHandle OpenSubmenuMenuHandle;
	void OpenSubmenuAfterTime();


	int32 ActiveBuilding;
	//TSubclassOf<AActor> ActivePreview;
	
	FVector PlaceLocation;
	FRotator Rotation;
	AActor* PreviewModel;

	bool placeBuildingButtonClicked;
	bool rotateBuildingButtonClicked;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category="RadialMenu")
	TArray<UTexture2D*>	Classes;
	UPROPERTY(EditAnywhere, Category="RadialMenu")
	TArray<int32> NumOfItemsInClasses;
	UPROPERTY(EditAnywhere, Category="RadialMenu")
	TArray<UTexture2D*> Items;
	
	UPROPERTY(EditAnywhere, Category="RadialMenu")
	TArray<TSubclassOf<AActor>> Buildings;
	UPROPERTY(EditAnywhere, Category="RadialMenu")
	TArray<TSubclassOf<AActor>> Previews;
	
	void AddClass(UTexture2D* icon);
	void SetClass(int i, UTexture2D* icon);
	void SetClassNum(int i, UTexture2D* defaultIcon);

	void AddClassItem(int Class, UTexture2D* icon);
	void SetClassItem(int Class, int i, UTexture2D* icon);
	void SetClassItemsNum(int Class, int i, UTexture2D* defaultIcon);

	void StartBuildingMode();
	void EndBuildingMode();
	
	void OpenMenu();
	void CloseMenu();

	UFUNCTION()
	void OnItemClicked(int i);

	UFUNCTION()
	void TraceLineBuild();


	void RotateBuilding();
	void StopRotatingBuilding();
	void PlaceBuilding();

	UPROPERTY(EditAnywhere, Category="Debug")
	bool ShowDebugLine;
};
