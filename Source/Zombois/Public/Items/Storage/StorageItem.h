// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "StorageItem.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBOIS_API AStorageItem : public AItem
{
	GENERATED_BODY()
	
public:
	AStorageItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Interaction")
	class UInventorySystemComponent* StorageInventoryComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
