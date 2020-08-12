// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Characters/Components/InventorySystemComponent.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = BaseCollisionVolume;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	IdleParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticlesComponent"));
	IdleParticlesComponent->SetupAttachment(GetRootComponent());

	bIdleParticleActive = false;
	bRotate = false;
	RotationRate = 45.f;

	CurrentItemState = EItemState::EIS_Pickup;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	BaseCollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
	BaseCollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);

	if (bIdleParticleActive && IdleParticlesComponent->Template)
	{
		IdleParticlesComponent->Activate();
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotate)
	{
		FRotator Rotation = GetActorRotation();
		Rotation.Yaw += DeltaTime * RotationRate;
		SetActorRotation(Rotation);
	}
}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin()"));

	if(CurrentItemState == EItemState::EIS_Pickup && OtherActor)
	{
		ACharacter* Char = Cast<ACharacter>(OtherActor);
		if (Char)
		{
			UInventorySystemComponent* InventorySys = Cast<UInventorySystemComponent>(Char->FindComponentByClass(UInventorySystemComponent::StaticClass()));
			if (InventorySys)
			{
				InventorySys->SetActiveOverlappingItem(this);
			}
		}
	}

	if (OverlapParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticles, GetActorLocation(), FRotator(0.0f), true);
	}
	if (OverlapSound)
	{
		UGameplayStatics::PlaySound2D(this, OverlapSound);
	}
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd()"));

	if (OtherActor)
	{
		ACharacter* Char = Cast<ACharacter>(OtherActor);
		if (Char)
		{
			UInventorySystemComponent* InventorySys = Cast<UInventorySystemComponent>(Char->FindComponentByClass(UInventorySystemComponent::StaticClass()));
			if (InventorySys)
			{
				InventorySys->SetActiveOverlappingItem(nullptr);
			}
		}
	}
}

