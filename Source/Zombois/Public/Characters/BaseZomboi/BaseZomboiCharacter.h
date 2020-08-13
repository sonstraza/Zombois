// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseZomboiCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus :uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Crouch UMETA(DisplayName = "Crouch"),
	EMS_ADS UMETA(DisplayName = "ADS"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),

	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class ZOMBOIS_API ABaseZomboiCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseZomboiCharacter();

	//Character Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Camera")
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Inventory")
	class UInventorySystemComponent* InventorySystem;

	//Movement Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Properties")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Properties")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Properties")
	float ADSWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Properties")
	float CrouchWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Properties")
	bool bSprintDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Properties")
	bool bADSDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Properties")
	bool bCrouchDown;

	/**
	 * \brief Current state of the player's movement.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement | Properties")
	EMovementStatus MovementStatus;

	//Camera Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement")
	float BaseLookUpRate;

	//Status Properties
	/**
	 * \brief The player's current health.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Health;

	/**
	 * \brief The max health the player can have.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float MaxHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement Functions
	void MoveForward(float Input);

	void MoveRight(float Input);

	void SprintDown();

	void SprintUp();

	void CrouchDown();

	void CrouchUp();

	void ADSDown();

	void ADSUp();

	void SetMovementStatus(EMovementStatus Status);

	//Camera Functions
	void Turn(float Input);

	void LookUp(float Input);

	//Item Functions
	UFUNCTION(BlueprintCallable)
	void PickupItem();

	UFUNCTION(BlueprintCallable)
	void DropItem();

	UFUNCTION(BlueprintCallable)
	void EquipItem();

	UFUNCTION(BlueprintCallable)
	void UnequipItem();

	UFUNCTION(BlueprintCallable)
	void OpenInventory();

	//Status Functions
	
	/**
	 * \brief This decreases the player's health.
	 * \param Amount The amount of health to take away from player.
	 */
	void DecrementHealth(float Amount);

	/**
	 * \brief This applies damage to the player.
	 * \param DamageAmount The amount of damage given to player.
	 * \param DamageEvent
	 * \param EventInstigator
	 * \param DamageCauser The damage causing actor to the player.
	 * \return
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/**
	 * \brief This starts the death sequence in motion.
	 */
	void Die();
};
