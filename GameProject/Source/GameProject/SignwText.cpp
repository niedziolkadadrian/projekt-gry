// Fill out your copyright notice in the Description page of Project Settings.


#include "SignwText.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASignwText::ASignwText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(VisualMesh);

	IsDialogOpened=false;
	TextDialog=FText::FromString("Sample Text");
}

// Called when the game starts or when spawned
void ASignwText::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASignwText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASignwText::OnInteract_Implementation(AActor* Caller){
	if(!IsDialogOpened){
		if(GetWorld()->GetTimerManager().IsTimerActive(FadeTimerHandle)){
			GetWorld()->GetTimerManager().PauseTimer(FadeTimerHandle);
		}
		AInGameHUD* InGameHUD=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if(InGameHUD){
			InGameHUD->GetDialogWidget()->ShowDialog(TextDialog);
		}

		IsDialogOpened=true;
	}
	else{
		FadeDialogWidget();
	}
	
}

void ASignwText::StartFocus_Implementation(){
	AInGameHUD* InGameHUD=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(InGameHUD){
		InGameHUD->GetHintWidget()->ShowHint(FText::FromString("Press E to talk"));
	}
}

void ASignwText::EndFocus_Implementation(){
	FadeDialogWidget();
	AInGameHUD* InGameHUD=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(InGameHUD){
		InGameHUD->GetHintWidget()->HideHint();
	}
}


void ASignwText::FadeDialogWidget(){
	AInGameHUD* InGameHUD=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(InGameHUD){
		InGameHUD->GetDialogWidget()->PlayDialogFadeAnim();
	}
	if(!GetWorld()->GetTimerManager().IsTimerActive(FadeTimerHandle)){
		GetWorld()->GetTimerManager().SetTimer(FadeTimerHandle, this, &ASignwText::HideDialogWidget,.5f,false);
	}
	IsDialogOpened=false;
}

void ASignwText::HideDialogWidget(){
	AInGameHUD* InGameHUD=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(InGameHUD){
		InGameHUD->GetDialogWidget()->HideDialog();
	}
}