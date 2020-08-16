// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseZomboi/BaseZomboiAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/BaseZomboi/BaseZomboiCharacter.h"

void UBaseZomboiAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			Zomboi = Cast<ABaseZomboiCharacter>(Pawn);
		}
	}
}

void UBaseZomboiAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
		bIsCrouching = Pawn->GetMovementComponent()->IsCrouching();

		if (Zomboi == nullptr)
		{
			Zomboi = Cast<ABaseZomboiCharacter>(Pawn);
		}

		MoveForward = Zomboi->GetInputAxisValue(FName("MoveForward"));
		MoveRight = Zomboi->GetInputAxisValue(FName("MoveRight"));

		bIsADS = Zomboi->bADSDown;
	}
}
