// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

AWeapon::AWeapon()
{
	MeleeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeCollision"));
	MeleeCollision->SetupAttachment(GetRootComponent());

	MeleeDamage = 25.f;

	bCanStack = false;
	bEquipable = true;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	MeleeCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::CombatOnOverlapBegin);
	MeleeCollision->OnComponentEndOverlap.AddDynamic(this, &AWeapon::CombatOnOverlapEnd);

	//Set Collision behavior for the weapon in combat
	MeleeCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeleeCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	MeleeCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MeleeCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	//TODO: Additional functionality for general overlap of items of type weapon.
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO:
	//Apply Damage
	//Play melee sound
	//Cause any other effects for this event to spawn or emit.
}

void AWeapon::CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AWeapon::ActivateMeleeCollision()
{
	MeleeCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AWeapon::DeactivateMeleeCollision()
{
	MeleeCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
