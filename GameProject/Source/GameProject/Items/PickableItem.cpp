// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"

// Sets default values
APickableItem::APickableItem()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	Mesh->SetupAttachment(RootComponent);

	InteractionZone = CreateDefaultSubobject<USphereComponent>(TEXT("SphereIntZone"));
	InteractionZone->SetupAttachment(Mesh);
	InteractionZone->SetSphereRadius(100.f);

	ToDestroy=false;
	Item=nullptr;
}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();
	SetItem(ItemClass, Item);
}

void APickableItem::OnInteract_Implementation(AActor* Caller)
{
	UInventoryComponent* Inv=Caller->FindComponentByClass<UInventoryComponent>();
	if(Inv){
		if(Inv->AddItem(Item)){
			this->SetActorHiddenInGame(true);
			Mesh->SetStaticMesh(nullptr);
			ToDestroy=true;
		}
	}	
}

void APickableItem::StartFocus_Implementation()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Jestem W");
}

void APickableItem::EndFocus_Implementation()
{
	if(ToDestroy)
		if(!this->IsPendingKill())
			this->Destroy(false,false);
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Jestem poza");
}

void APickableItem::SetItem(TSubclassOf<UItemBase> itmClass,UItemBase* itm)
{
	if(!itm){
		if(itmClass){
			this->ItemClass=itmClass;
			Item = NewObject<UItemBase>(GetWorld(),ItemClass);
			Item->Quantity=60;
   		}
	}
	if(itm && itmClass){
		this->ItemClass=itmClass;
		this->Item=itm;
	}
	if(Item)
		Mesh->SetStaticMesh(Item->PickupMesh);
}

