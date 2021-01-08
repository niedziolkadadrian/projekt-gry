// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputStateMachine.generated.h"


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
	enum class State{PlayerInput, Building, UI_CraftInv, UI_Dialog, UI_BuildingMenu};

	UInputStateMachine::State ActState;
	UInputStateMachine::State BeforeUI;	
};
