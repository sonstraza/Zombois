// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseZomboiAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBOIS_API UBaseZomboiAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class ABaseZomboiCharacter* Zomboi;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MoveForward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MoveRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsADS;
};
