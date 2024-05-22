// Copyright 2023 Teyon. All Rights Reserved.


#include "PlayerVehicle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "PlayerControllerBase.h"

APlayerVehicle::APlayerVehicle()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("Spring Arm"));
	SpringArm->SetupAttachment(GetRootComponent());

	CameraFromAbove = CreateDefaultSubobject<UCameraComponent>(FName("Camera From Above"));
	CameraFromAbove->SetupAttachment(SpringArm);

	FrontCamera = CreateDefaultSubobject<UCameraComponent>(FName("Front Camera"));
	FrontCamera->SetupAttachment(GetMesh(), FName("HoodGameplayCamera"));

	FrontCamera->SetActive(false);

	CarInteriorCamera = CreateDefaultSubobject<UCameraComponent>(FName("Car Interior Camera"));
	CarInteriorCamera->SetupAttachment(GetMesh(), FName("CarInteriorGameplayCamera"));

	CarInteriorCamera->SetActive(true);
}

void APlayerVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (SteeringAction)
		{
			EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &APlayerVehicle::Steering);
			EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &APlayerVehicle::Steering);
		}

		if (ThrottleAction)
		{
			EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &APlayerVehicle::Throttle);
			EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &APlayerVehicle::Throttle);
		}

		if (BrakeAction)
		{
			EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &APlayerVehicle::Brake);
			EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &APlayerVehicle::Brake);
		}

		if (HandbrakeAction)
		{
			EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &APlayerVehicle::StartHandbrake);
			EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &APlayerVehicle::StopHandbrake);
		}
	}
}

void APlayerVehicle::Steering(const FInputActionValue& Value)
{
	const float SteeringValue = Value.Get<float>();

	GetVehicleMovement()->SetSteeringInput(SteeringValue);
}

void APlayerVehicle::Throttle(const FInputActionValue& Value)
{
	const float ThrottleValue = Value.Get<float>();

	GetVehicleMovement()->SetThrottleInput(ThrottleValue);
}

void APlayerVehicle::Brake(const FInputActionValue& Value)
{
	const float BreakValue = Value.Get<float>();

	GetVehicleMovement()->SetBrakeInput(BreakValue);
}

void APlayerVehicle::StartHandbrake(const FInputActionValue& Value)
{
	GetVehicleMovement()->SetHandbrakeInput(true);
}

void APlayerVehicle::StopHandbrake(const FInputActionValue& Value)
{
	GetVehicleMovement()->SetHandbrakeInput(false);
}

void APlayerVehicle::RaceFinished()
{
	if (APlayerControllerBase* const PlayerController = Cast<APlayerControllerBase>(GetController()))
	{
		PlayerController->RaceFinished();
	}
}