// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "I_SignInterract.h"
#include "SignwText.generated.h"

UCLASS()
class GAMEPROJECT_API ASignwText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASignwText();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	virtual bool ReactToEnter();

	UFUNCTION(BlueprintCallable, Category = "Sign")
	void showWidget();

};
