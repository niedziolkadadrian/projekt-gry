// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


#include "DrawDebugHelpers.h"

//////////////////////////////////////////////////////////////////////////
// AGameProjectCharacter

AGameProjectCharacter::AGameProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapsule"));
	TriggerCapsule->InitCapsuleSize(42.f, 96.0f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this,&AGameProjectCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AGameProjectCharacter::OnOverlapEnd);

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	Inventory->Size=FVector2D(9.f,4.f);

	OverlappedInteractActors=0;
	FocusedActor=nullptr;
	IsInvOpen=false;

	Hunger=100.f;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGameProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Akcje
	PlayerInputComponent->BindAction("Interact", IE_Pressed,  this, &AGameProjectCharacter::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGameProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGameProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGameProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGameProjectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AGameProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AGameProjectCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AGameProjectCharacter::OnResetVR);
}


void AGameProjectCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AGameProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AGameProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AGameProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGameProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGameProjectCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGameProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AGameProjectCharacter::Interact(){
	if(OverlappedInteractActors && FocusedActor){
		IInteractInterface* InteractInt=Cast<IInteractInterface>(FocusedActor);
		if(InteractInt && AActor::IsOverlappingActor(FocusedActor)){	//jeżeli ma on InteractInterface
			InteractInt->Execute_OnInteract(FocusedActor, this);
		}
		else{		//jeżeli nie ma InteractInterface lub jestem poza zasięgiem
			OpenCloseInventory();
		}	
	}else{
		OpenCloseInventory();
	}
	 
}


void AGameProjectCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if(OtherActor && (OtherActor != this) && OtherComp){
		IInteractInterface* InteractInt=Cast<IInteractInterface>(OtherActor);
		if(InteractInt){	//jeżeli ma InteractInterface
			if(!OverlappedInteractActors){	//if it's first start checking what player is looking at
				if(!GetWorld()->GetTimerManager().IsTimerActive(LTraceTimerHandle))
					GetWorld()->GetTimerManager().SetTimer(LTraceTimerHandle, this, &AGameProjectCharacter::TraceLine,0.1f,true);
			}
			OverlappedInteractActors++;
		}
	}
}

void AGameProjectCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
	IInteractInterface* InteractInt=Cast<IInteractInterface>(OtherActor);
	if(InteractInt){	//jeżeli ma InteractInterface
		OverlappedInteractActors--;
		if(!OverlappedInteractActors){	//if it's last stop checking what player is looking at
			
			if(GetWorld()->GetTimerManager().IsTimerActive(LTraceTimerHandle))
				GetWorld()->GetTimerManager().PauseTimer(LTraceTimerHandle);
		
			if(FocusedActor){	//jeżeli był jakiś poprzednio patrzony aktor
				IInteractInterface* FocusedInteractInt=Cast<IInteractInterface>(FocusedActor);
				if(FocusedInteractInt){	//jeżeli miał on InteractInterface
					FocusedInteractInt->Execute_EndFocus(FocusedActor);
				}
			}	
			FocusedActor=nullptr;	//ustawiam FocusedActor na nullptr
		}
	}
	
}

void AGameProjectCharacter::TraceLine(){
	FVector Loc;
	FRotator Rot;
	FHitResult Hit;

	GetController()->GetPlayerViewPoint(Loc, Rot);
	FVector End=Loc+(Rot.Vector()*2000);

	FCollisionQueryParams TraceParams;

	bool IsHit=GetWorld()->LineTraceSingleByChannel(Hit,Loc,End,ECC_Visibility,TraceParams);

	AActor* HittedActor=Hit.GetActor();
	if(HittedActor){	//jeżeli cokolwiek trafiono
		if(HittedActor != FocusedActor){	//jeżeli nowy aktor != poprzednio aktor na ktory sie patrzylem
			if(FocusedActor){				//jeżeli był jakiś poprzednio patrzony aktor
				IInteractInterface* InteractInt=Cast<IInteractInterface>(FocusedActor);
				if(InteractInt){			//jeżeli miał InteractInterface
					InteractInt->Execute_EndFocus(FocusedActor);
				}
			}
			//nowo patrzony aktor
			IInteractInterface* InteractInt=Cast<IInteractInterface>(HittedActor);
			if(InteractInt && AActor::IsOverlappingActor(HittedActor)){	//jeżeli ma InteractInterface
				InteractInt->Execute_StartFocus(HittedActor);
			}
			FocusedActor=HittedActor; //ustawiam FocusedActor na dowolnego typu nowy aktor
		}
	}
	else{	//jeżeli nic nie trafiono
		if(FocusedActor){	//jeżeli był jakiś poprzednio patrzony aktor
			IInteractInterface* InteractInt=Cast<IInteractInterface>(FocusedActor);
			if(InteractInt){	//jeżeli miał on InteractInterface
				InteractInt->Execute_EndFocus(FocusedActor);
			}
		}	
		FocusedActor=nullptr;	//ustawiam FocusedActor na nullptr
	}
	
	if(ShowDebugLine)
		DrawDebugLine(GetWorld(),Loc,End,FColor::Red,false,2.f);
}

void AGameProjectCharacter::OpenCloseInventory(){
	if(!IsInvOpen){
		AInGameHUD* InGameHUD=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if(InGameHUD){
			InGameHUD->GetInventoryWidget()->ShowInventory();
		}
		IsInvOpen=true;
	}
	else{
		AInGameHUD* InGameHUD=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if(InGameHUD){
			InGameHUD->GetInventoryWidget()->HideInventory();
		}
		IsInvOpen=false;
	}
}

void AGameProjectCharacter::UseItem(class UItemBase* Item){
	if(Item){
		Item->OnUse(this);
	}
}