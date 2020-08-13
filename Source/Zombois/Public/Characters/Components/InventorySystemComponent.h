// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystemComponent.generated.h"

class AItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBOIS_API UInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventorySystemComponent();

	/**
	 * \brief Pickupable item that is in the current vicinity of the player.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	AItem* ActiveOverlappingItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	AItem* EquippedItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	TArray<AItem*> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	int InventoryMaxCapacity;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }

	UFUNCTION(BlueprintCallable)
	bool AddItemToInventory(AItem* Item);

	UFUNCTION(BlueprintCallable)
	bool RemoveItemFromInventory(AItem* Item, bool bDropItem);

	UFUNCTION(BlueprintCallable)
	void ClearInventory(bool bDropInventory);

	UFUNCTION(BlueprintCallable)
	bool EquipItem(AItem* Item, FName SocketName);

	UFUNCTION(BlueprintCallable)
	bool UnequipItem(AItem* Item);
};
