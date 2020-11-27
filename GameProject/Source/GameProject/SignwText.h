// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/InteractInterface.h"
#include "UI/InGameHUD.h"
#include "SignwText.generated.h"

UCLASS()
class GAMEPROJECT_API ASignwText : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASignwText();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	bool IsDialogOpened;
	FTimerHandle FadeTimerHandle;
	void FadeDialogWidget();
	UFUNCTION()
	void HideDialogWidget();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void StartFocus();
	virtual void StartFocus_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void EndFocus();
	virtual void EndFocus_Implementation();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog")
	FText TextDialog;
};
