// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseZomboi/BaseZomboiCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ABaseZomboiCharacter::ABaseZomboiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Components Initialization
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCamera->SetupAttachment(RootComponent);

	//Variable Initial Values (Subject to change)

	//Movement
	WalkSpeed = 650.f;
	SprintSpeed = 1000.f;
	ADSWalkSpeed = 500.f;
	CrouchWalkSpeed = 450.f;

	bSprintDown = false;
	bCrouchDown = false;
	bADSDown = false;

	SetMovementStatus(EMovementStatus::EMS_Normal);

	GetCharacterMovement()->JumpZVelocity = 500.f;

	//Camera
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;
}

// Called when the game starts or when spawned
void ABaseZomboiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseZomboiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseZomboiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseZomboiCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseZomboiCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ABaseZomboiCharacter::SprintDown);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ABaseZomboiCharacter::SprintUp);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ABaseZomboiCharacter::CrouchDown);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &ABaseZomboiCharacter::CrouchUp);

	PlayerInputComponent->BindAction(TEXT("ADS"), IE_Pressed, this, &ABaseZomboiCharacter::ADSDown);
	PlayerInputComponent->BindAction(TEXT("ADS"), IE_Released, this, &ABaseZomboiCharacter::ADSUp);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABaseZomboiCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABaseZomboiCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);

}

void ABaseZomboiCharacter::MoveForward(float Input)
{
	if ((Controller != nullptr) && (Input != 0))
	{
		//find out the forward vector
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Input);
	}
}

void ABaseZomboiCharacter::MoveRight(float Input)
{
	if ((Controller != nullptr) && (Input != 0))
	{
		//find out the right vector
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Input);
	}
}

void ABaseZomboiCharacter::SprintDown()
{
	bSprintDown = true;
	SetMovementStatus(EMovementStatus::EMS_Sprinting);
}

void ABaseZomboiCharacter::SprintUp()
{
	bSprintDown = false;
	SetMovementStatus(EMovementStatus::EMS_Normal);
}

void ABaseZomboiCharacter::CrouchDown()
{
	bCrouchDown = true;
	SetMovementStatus(EMovementStatus::EMS_Crouch);
}

void ABaseZomboiCharacter::CrouchUp()
{
	bCrouchDown = false;
	SetMovementStatus(EMovementStatus::EMS_Normal);
}

void ABaseZomboiCharacter::ADSDown()
{
	bADSDown = true;
	SetMovementStatus(EMovementStatus::EMS_ADS);
}

void ABaseZomboiCharacter::ADSUp()
{
	bADSDown = false;
	SetMovementStatus(EMovementStatus::EMS_Normal);
}

void ABaseZomboiCharacter::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status;
	switch (Status) {
	case EMovementStatus::EMS_Sprinting:
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		break;

	case EMovementStatus::EMS_Normal:
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		break;

	case EMovementStatus::EMS_Crouch:
		GetCharacterMovement()->MaxWalkSpeed = CrouchWalkSpeed;
		break;

	case EMovementStatus::EMS_ADS:
		GetCharacterMovement()->MaxWalkSpeed = ADSWalkSpeed;
		break;
	}
}

void ABaseZomboiCharacter::Turn(float Input)
{
	AddControllerYawInput(Input * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseZomboiCharacter::LookUp(float Input)
{
	AddControllerPitchInput(Input * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

