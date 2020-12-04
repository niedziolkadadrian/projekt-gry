// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"

// Sets default values
APickableItem::APickableItem()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	Mesh->SetupAttachment(RootComponent);

	InteractionZone = CreateDefaultSubobject<USphereComponent>(TEXT("SphereIntZone"));
	InteractionZone->SetupAttachment(Mesh);

	ToDestroy=false;
	Item=nullptr;
}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();
	if(!Item){
		if(ItemClass){
			Item = NewObject<UItemBase>(GetWorld(),ItemClass);
			Item->Quantity=60;
   		}
	}
	if(Item){
		Mesh->SetStaticMesh(Item->PickupMesh);
	}
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
	/*AGameProjectCharacter* Character=Cast<AGameProjectCharacter>(Caller);
	if(Character){
		if(Character->GetInventory())
			if(Character->GetInventory()->AddItem(Item))
				this->Destroy();
	}*/
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

void APickableItem::SetItem(TSubclassOf<UItemBase> ItmClass,UItemBase* Itm)
{
	this->ItemClass=ItmClass;
	this->Item=Itm;
}

