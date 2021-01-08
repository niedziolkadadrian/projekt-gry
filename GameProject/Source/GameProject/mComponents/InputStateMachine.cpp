// Fill out your copyright notice in the Description page of Project Settings.


#include "InputStateMachine.h"

// Sets default values for this component's properties
UInputStateMachine::UInputStateMachine()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInputStateMachine::BeginPlay()
{
	Super::BeginPlay();
	ActState=UInputStateMachine::State::PlayerInput;
	BeforeUI=UInputStateMachine::State::PlayerInput;
}

