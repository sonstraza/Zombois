// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystemComponent.generated.h"

class AItem;

USTRUCT(BlueprintType)
struct FItemStack
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<AItem*> StackedItems;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBOIS_API UInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventorySystemComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class USphereComponent* DropItemLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	class ACharacter* Char;

	/**
	 * \brief Pickupable item that is in the current vicinity of the player.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	AItem* ActiveOverlappingItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	AItem* EquippedItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	TMap<FName, FItemStack> Inventory;

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
