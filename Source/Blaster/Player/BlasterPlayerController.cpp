// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/Input/BlasterEnhancedInputComponent.h"
#include "Components/InputComponent.h"

ABlasterPlayerController::ABlasterPlayerController()
{
	bReplicates = true;
}

void ABlasterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(BlasterContext, 0);
	}
	
}

void ABlasterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UBlasterEnhancedInputComponent* BlasterInputComponent = CastChecked<UBlasterEnhancedInputComponent>(InputComponent))
	{
		BlasterInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ABlasterPlayerController::Move);
		BlasterInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ABlasterPlayerController::Look);
		BlasterInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this,&ABlasterPlayerController::Jump);
	}
}

void ABlasterPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		//find out which way is forward
		const FRotator ControlRot = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRot.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABlasterPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookVectorValue = InputActionValue.Get<FVector2D>();

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookVectorValue.X);
		ControlledPawn->AddControllerPitchInput(LookVectorValue.Y);
	}
}

void ABlasterPlayerController::Jump()
{
	GetCharacter()->Jump();	
}
