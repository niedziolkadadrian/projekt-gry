// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_SignInterract.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UI_SignInterract : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPROJECT_API II_SignInterract
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool ReactToEnter();
	
};