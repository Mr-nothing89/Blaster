// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterAnimInstance.h"

#include "BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	/**
           * Attempts to assign `TryGetPawnOwner()` to `BlasterCharacter`. 
           * Needs to be a valid `ABlasterCharacter` or else it aborts the function early.
           */
          if(BlasterCharacter == nullptr)
          {
          	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
          }
          if(BlasterCharacter == nullptr) return;
          
          /**
           * Measures the 2D velocity (on the XY plane) of `BlasterCharacter`. 
           * This is probably used to control animations based on the character's speed.
           */
          Speed = UKismetMathLibrary::VSizeXY(BlasterCharacter->GetVelocity());
          
          /**
           * Checks if `BlasterCharacter` is in the air by verifying if it is falling.
           * Can be used in deciding which animations to play (example: jump, fall, etc.)
           */
          bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();
          
          /**
           * Checks if `BlasterCharacter` is accelerating by comparing if the current acceleration magnitude is greater than 0.
           * Useful in determining if the character is in idle or moving state.
           */
          bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
}
