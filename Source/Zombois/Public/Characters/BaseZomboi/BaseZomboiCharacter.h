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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components/Camera")
	class UCameraComponent* FirstPersonCamera;

	//Movement Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement/Variables")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement/Variables")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement/Variables")
	float ADSWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement/Variables")
	float CrouchWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement/Variables")
	bool bSprintDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement/Variables")
	bool bADSDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement/Variables")
	bool bCrouchDown;

	/**
	 * \brief Current state of the player's movement.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement/Enums")
	EMovementStatus MovementStatus;

	//Camera Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement")
	float BaseLookUpRate;

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


};
