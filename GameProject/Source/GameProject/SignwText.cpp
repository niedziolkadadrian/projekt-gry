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

bool ASignwText::ReactToEnter()
{
	return true;
}

void ASignwText::showWidget()
{
}

