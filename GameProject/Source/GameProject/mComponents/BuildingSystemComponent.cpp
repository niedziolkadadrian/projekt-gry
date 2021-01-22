// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystemComponent.h"

// Sets default values for this component's properties
UBuildingSystemComponent::UBuildingSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	RadialInputInitialized=false;
	ShowDebugLine=false;
	ActiveBuilding=-1;
	PreviewModel=nullptr;

	placeBuildingButtonClicked=false;
	rotateBuildingButtonClicked=false;
	

	Rotation=FRotator(.0f,.0f,.0f);
}


void UBuildingSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Actor=Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(Actor){
        InputStateMachine=Actor->FindComponentByClass<UInputStateMachine>();
		
		if(Actor->InputComponent){
			Actor->InputComponent->BindAction("BuildingMenu", IE_Pressed,  this, &UBuildingSystemComponent::OpenMenu);
			Actor->InputComponent->BindAction("BuildingMenu", IE_Released,  this, &UBuildingSystemComponent::CloseMenu);
			
			Actor->InputComponent->BindAction("PlaceBuilding", IE_Released,  this, &UBuildingSystemComponent::PlaceBuilding);
			
			Actor->InputComponent->BindAction("RotateBuilding", IE_Pressed,  this, &UBuildingSystemComponent::RotateBuilding);
			Actor->InputComponent->BindAction("RotateBuilding", IE_Released,  this, &UBuildingSystemComponent::StopRotatingBuilding);
		}
			
	}
	
	InGameHUD=Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	int32 startI=0;
	for(int i=0;i<Classes.Num();i++){
		if(startI>0)
			StartIndex.Add(startI-1);
		else
			StartIndex.Add(0);
		
		startI+=NumOfItemsInClasses[i];
	}
}

// Called every frame
void UBuildingSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Budowanie
	if(ActiveBuilding>=0){
		if(!PreviewModel){
			PreviewModel=GetWorld()->SpawnActor(Previews[ActiveBuilding].Get(),new FVector(.0f,.0f,.0f),new FRotator(.0f,.0f,.0f),FActorSpawnParameters());
		}
			
		TraceLineBuild();
		if(rotateBuildingButtonClicked){
			Rotation.Yaw+=22.5f*DeltaTime;
			Rotation=Rotation.Clamp();
			
			//PreviewModel->SetActorRotation(Rotation,ETeleportType::None);
		}
		if(!PlaceLocation.Equals(FVector(0,0,0),0)){
			PreviewModel->SetActorLocationAndRotation(PlaceLocation,Rotation, false, 0, ETeleportType::ResetPhysics);
			
			if(placeBuildingButtonClicked){
				if(GEngine)
      				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Budowanko bud bud")));
	
				ABuldingPreview* prev=Cast<ABuldingPreview>(PreviewModel);
				if(prev){
					if(GEngine)
      					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("PREVIEW")));
					if(prev->canBePlaced){
						if(GEngine)
      						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("CAN BE PLACED")));
						GetWorld()->SpawnActor(Buildings[ActiveBuilding].Get(), &PlaceLocation, &Rotation, FActorSpawnParameters());
						//Remove resources
						UInventoryComponent* Inventory=GetOwner()->FindComponentByClass<UInventoryComponent>();
						if(Inventory){
							for(int i=0;i<prev->BuildResources.Num();i++){
								UItemBase* Ingredient=prev->BuildResources[i].GetDefaultObject();
								if(Ingredient && i<prev->BuildResourcesQuantity.Num()){
									Inventory->RemoveItems(Ingredient,prev->BuildResourcesQuantity[i]);
								}
							}
						}
					}
				}
				placeBuildingButtonClicked=false;
			}	
		}
		else{
			PreviewModel->SetActorHiddenInGame(true);
			PreviewModel->Destroy();
			PreviewModel=nullptr;
		}
	}
}


void UBuildingSystemComponent::StartBuildingMode(){
	InputStateMachine->ActState=InputState::Building;
}

void UBuildingSystemComponent::EndBuildingMode(){
	ActiveBuilding=-1;
	
	if(PreviewModel){
		PreviewModel->SetActorHiddenInGame(true);
		PreviewModel->Destroy();
		PreviewModel=nullptr;
	}
	

	InputStateMachine->ActState=InputState::PlayerInput;
}


void UBuildingSystemComponent::OpenMenu(){
	//zmienic na tylko building
	if(InputStateMachine->ActState==InputState::Building)
	{
		if(InGameHUD){
			if(!RadialInputInitialized){
				InGameHUD->GetRadialMenuWidget()->OnRadialItemClicked.AddDynamic(this, &UBuildingSystemComponent::OnItemClicked);
				RadialInputInitialized=true;
			}
				
			InGameHUD->ActiveUIElems++;
			InGameHUD->ChangeInputType();
			Class=-1;
			
			//---------------------
			//Classowe elementy do widgeta i ikonki
			InGameHUD->GetRadialMenuWidget()->SetNumOfElems(Classes.Num());
			for(int i=0;i<Classes.Num();i++){
				if(Classes[i])
					InGameHUD->GetRadialMenuWidget()->SetElemIcon(i,Classes[i]);
			}
			//
			InGameHUD->GetRadialMenuWidget()->ShowRadialMenu();
			
            InputStateMachine->BeforeUI=InputStateMachine->ActState;
			InputStateMachine->ActState=InputState::UI_BuildingMenu;
		}
	}
}

void UBuildingSystemComponent::CloseMenu(){
	if(GEngine)
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("ClosingMenu")));
	
	if(InputStateMachine->ActState==InputState::UI_BuildingMenu){
		if(InGameHUD){
			InGameHUD->ActiveUIElems--;
			InGameHUD->ChangeInputType();
			InGameHUD->GetRadialMenuWidget()->HideRadialMenu();
			
			InputStateMachine->ActState=InputStateMachine->BeforeUI;
		}
	}
}

void UBuildingSystemComponent::OpenSubmenuAfterTime(){
	if(InGameHUD){
		InGameHUD->ActiveUIElems++;
		InGameHUD->ChangeInputType();
		InGameHUD->GetRadialMenuWidget()->ShowRadialMenu();
		
		InputStateMachine->BeforeUI=InputStateMachine->ActState;
		InputStateMachine->ActState=InputState::UI_BuildingMenu;
	}
	if(GEngine)
      	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("%d"),Class));
}



void UBuildingSystemComponent::OnItemClicked(int32 index){
	if(Class==-1){
		switch(index){
			case 0:
				ActiveBuilding=-1;
				CloseMenu();
				break;
			case 1:
				CloseMenu();
				//---------------------
				//Ustaw liczbe elementow i ikonki, otwórz nowe menu
				if(InGameHUD){
					InGameHUD->GetRadialMenuWidget()->SetNumOfElems(NumOfItemsInClasses[1]);
					for(int i=0;i<NumOfItemsInClasses[1];i++){
						if(Items[StartIndex[1]+i])
							InGameHUD->GetRadialMenuWidget()->SetElemIcon(i,Items[StartIndex[1]+i]);
					}
					
					if(!GetWorld()->GetTimerManager().IsTimerActive(OpenSubmenuMenuHandle))
						GetWorld()->GetTimerManager().SetTimer(OpenSubmenuMenuHandle, this, &UBuildingSystemComponent::OpenSubmenuAfterTime,0.1f,false);
				}
				//
				Class=1;
				break;
			case 2:
				CloseMenu();
				Class=2;
				break;
			default:
				CloseMenu();
				break;
		}
	}
	else{
		switch(Class){
			case 1:
				if(GEngine)
      				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Classa 1")));
				switch(index){
					case 0:
						CloseMenu();
						//---------------------
						//Ustaw liczbe elementow i ikonki, powróć do menu klas
						if(InGameHUD){
							InGameHUD->GetRadialMenuWidget()->SetNumOfElems(Classes.Num());
							for(int i=0;i<Classes.Num();i++){
								if(Classes[i])
									InGameHUD->GetRadialMenuWidget()->SetElemIcon(i,Classes[i]);
							}
							
							if(!GetWorld()->GetTimerManager().IsTimerActive(OpenSubmenuMenuHandle))
								GetWorld()->GetTimerManager().SetTimer(OpenSubmenuMenuHandle, this, &UBuildingSystemComponent::OpenSubmenuAfterTime,0.1f,false);
						}
						//
						Class=-1;
						break;
					case 1:
						if(GEngine)
      						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Wybrano budyneczek")));
	
						ActiveBuilding=0;
						CloseMenu();
						break;
					case 2:
					
					case 3:
					
					default:
						CloseMenu();
						break;
				}
				break;
			case 2:

			default:
				CloseMenu();
				break;
		}
	}
}

void UBuildingSystemComponent::RotateBuilding(){
	if(InputStateMachine->ActState==InputState::Building &&
	   ActiveBuilding>=0)
	{
		rotateBuildingButtonClicked=true;
	}
}
void UBuildingSystemComponent::StopRotatingBuilding(){
	if(InputStateMachine->ActState==InputState::Building &&
	   ActiveBuilding>=0)
	{
		rotateBuildingButtonClicked=false;
	}
}

void UBuildingSystemComponent::PlaceBuilding(){
	/*if(InputStateMachine->ActState==InputState::Building ||
	 	InputStateMachine->ActState==InputState::PlayerInput &&
		placeBuildEnabled)
	{
		if(!PlaceLocation.Equals(FVector(0,0,0),0)){
			if(GEngine)
      			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Postawiono")));
	
		}
	}*/
	if(InputStateMachine->ActState==InputState::Building &&
	   ActiveBuilding>=0)
	{
		if(GEngine)
      			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Stawianie")));
	
		placeBuildingButtonClicked=true;
	}
}

void UBuildingSystemComponent::TraceLineBuild(){
	FVector Loc;
	FRotator Rot;
	FHitResult Hit;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Loc, Rot);
	FVector End=Loc+(Rot.Vector()*20000);

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner());
	
	bool IsHit=GetWorld()->LineTraceSingleByChannel(Hit,Loc,End,ECC_Visibility,TraceParams);
	if(IsHit){
		PlaceLocation=Hit.ImpactPoint;
	}
	else{
		PlaceLocation=FVector(0,0,0);
	}

	if(ShowDebugLine)
		DrawDebugLine(GetWorld(),Loc,End,FColor::Red,false,2.f);
}
