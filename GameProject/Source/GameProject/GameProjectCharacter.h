// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/EngineTypes.h"
#include "Interfaces/InteractInterface.h"
#include "UI/InGameHUD.h"
#include "Items/ItemBase.h"
#include "mComponents/InventoryComponent.h"

#include "GameProjectCharacter.generated.h"

UCLASS(config=Game)
class AGameProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//Trigger capsule
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Trigger Capsule", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* TriggerCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;
public:
	AGameProjectCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE class UInventoryComponent* GetInvenotry() const { return Inventory; }

//-------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category="Debug")
	bool ShowDebugLine;

	UPROPERTY(EditAnywhere, Category="InventorySize")
	FIntPoint PlayerInventorySize;

	//zegar dla sprawdzania na co patrzy się postać, gdy OverlappedInteractActors > 0
	FTimerHandle LTraceTimerHandle;

	//Wywoływane w momencie nacisnięcia przycisku interakcji
	void Interact();

	void OpenCrafting();

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category="Needs")
	float Hunger;

	UFUNCTION(BlueprintCallable, Category="Item")
	void UseItem(class UItemBase* Item);
private:

	int32 OverlappedInteractActors;
	AActor* FocusedActor;
	bool IsInvOpen;
	bool IsCraftOpen;

	UFUNCTION()
	void TraceLine();

	void OpenCloseInventory();
	
	UFUNCTION()
	void OnUpdateInventory();

};

