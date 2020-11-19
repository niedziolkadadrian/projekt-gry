// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/Actor.h"
#include "ChangeCamera.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AChangeCamera : public APlayerCameraManager
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	AActor* myActor;
};
