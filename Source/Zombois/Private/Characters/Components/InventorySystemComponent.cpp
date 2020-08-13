// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/InventorySystemComponent.h"
#include "Items/Item.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UInventorySystemComponent::UInventorySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventorySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventorySystemComponent::AddItemToInventory(AItem* Item)
{
	if (Inventory.Contains(Item)) //Check if contains means by reference or by value.
	{
		return false;
	}

	//TODO: Copy Item, destroy spawned item, store copy.

	Inventory.Add(Item);

	return true;
}

bool UInventorySystemComponent::RemoveItemFromInventory(AItem* Item, bool bDropItem)
{
	if (!Inventory.Contains(Item))
	{
		return false;
	}

	if (!bDropItem)
	{
		Inventory.Remove(Item);
	}
	else
	{
		//TODO: Spawn copy of dropped Item then remove original from Inventory
		Inventory.Remove(Item);
	}

	return true;
}

void UInventorySystemComponent::ClearInventory(bool bDropInventory)
{
	if (!bDropInventory)
	{
		Inventory.Empty();
	}
	else
	{
		//TODO: Spawn items in some sort of package or as individual items and drop on ground in front of player
		// Then empty Inventory.
	}
	
}

bool UInventorySystemComponent::EquipItem(AItem* Item, FName SocketName)
{
	if (!Inventory.Contains(Item) && ActiveOverlappingItem == Item)
	{
		AddItemToInventory(Item);
	}

	ACharacter* Char = Cast<ACharacter>(GetOwner());

	if (Char)
	{
		Item->SetInstigator(Char->GetController());

		//Setting skeletal mesh to ignore collision with pawn and camera
		Item->Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		Item->Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		Item->Mesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* RightHandSocket = Char->GetMesh()->GetSocketByName(SocketName);

		if (RightHandSocket)
		{
			RightHandSocket->AttachActor(Item, Char->GetMesh());
			Item->bRotate = false;

			if (ActiveOverlappingItem == Item)
			{
				SetActiveOverlappingItem(nullptr);
			}
			
			Item->CurrentItemState = EItemState::EIS_Equipped;

			if (Item->OnEquipSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), Item->OnEquipSound, Item->GetActorLocation());
			}
			if (Item->bIdleParticleActive)
			{
				Item->IdleParticlesComponent->Deactivate();
				Item->bIdleParticleActive = false;
			}

			return true;
		}
	}

	return false;
}

bool UInventorySystemComponent::UnequipItem(AItem* Item)
{
	if (!Inventory.Contains(Item) || Item->CurrentItemState != EItemState::EIS_Equipped)
	{
		return false;
	}

	ACharacter* Char = Cast<ACharacter>(GetOwner());

	if (Char)
	{
		Item->SetInstigator(nullptr);

		//Setting skeletal mesh to no longer ignore collision with pawn and camera
		Item->Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
		Item->Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

		Item->Mesh->SetSimulatePhysics(true);

		Item->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

		if (Item->OnUnequipSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Item->OnUnequipSound, Item->GetActorLocation());
		}

		return true;
	}

	return false;
}

