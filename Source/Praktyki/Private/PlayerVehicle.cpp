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

	CarInteriorCamera = CreateDefaultSubobject<UCameraComponent>(FName("Car Interior Camera"));
	CarInteriorCamera->SetupAttachment(GetMesh(), FName("CarInteriorGameplayCamera"));

	Cameras.Add(CameraFromAbove);
	Cameras.Add(FrontCamera);
	Cameras.Add(CarInteriorCamera);
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

		if (SwitchToNextCameraAction)
		{
			EnhancedInputComponent->BindAction(SwitchToNextCameraAction, ETriggerEvent::Started, this, &APlayerVehicle::SwitchToNextCamera);
		}

		if (SwitchToCameraFromAboveAction)
		{
			EnhancedInputComponent->BindAction(SwitchToCameraFromAboveAction, ETriggerEvent::Started, this, &APlayerVehicle::SwitchToCameraFromAbove);
		}

		if (SwitchToFrontCameraAction)
		{
			EnhancedInputComponent->BindAction(SwitchToFrontCameraAction, ETriggerEvent::Started, this, &APlayerVehicle::SwitchToFrontCamera);
		}

		if (SwitchToCarInteriorCameraAction)
		{
			EnhancedInputComponent->BindAction(SwitchToCarInteriorCameraAction, ETriggerEvent::Started, this, &APlayerVehicle::SwitchToCarInteriorCamera);
		}
	}
}

void APlayerVehicle::BeginPlay()
{
	Super::BeginPlay();

	CarInteriorCamera->SetActive(false);
	FrontCamera->SetActive(false);
}

void APlayerVehicle::Steering(const FInputActionValue& Value)
{
	const float SteeringValue = Value.Get<float>();

	GetVehicleMovement()->SetSteeringInput(SteeringValue);
}

void APlayerVehicle::Throttle(const FInputActionValue& Value)
{
	float ThrottleValue = Value.Get<float>();

	if (bBlockThrottle)
	{
		ThrottleValue = 0.f;
	}

	GetVehicleMovement()->SetThrottleInput(ThrottleValue);
	UE_LOG(LogTemp, Warning, TEXT("Throttle input: %f"), ThrottleValue);
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

void APlayerVehicle::SwitchToNextCamera()
{
	if (Cameras[CurrentCameraIndex])
	{
		Cameras[CurrentCameraIndex]->SetActive(false);
	}

	++CurrentCameraIndex;
	if (CurrentCameraIndex == Cameras.Num())
	{
		CurrentCameraIndex = 0;
	}

	if (Cameras[CurrentCameraIndex])
	{
		Cameras[CurrentCameraIndex]->SetActive(true);
	}
}

void APlayerVehicle::SwitchToCameraFromAbove()
{
	SwitchToCamera(CameraFromAbove);
}

void APlayerVehicle::SwitchToFrontCamera()
{
	SwitchToCamera(FrontCamera);
}

void APlayerVehicle::SwitchToCarInteriorCamera()
{
	SwitchToCamera(CarInteriorCamera);
}

void APlayerVehicle::SwitchToCamera(UCameraComponent* const CameraToSwitchOn)
{
	if (CameraToSwitchOn)
	{
		if (Cameras[CurrentCameraIndex])
		{
			Cameras[CurrentCameraIndex]->SetActive(false);
		}

		int32 CameraIndex;
		if (Cameras.Find(CameraToSwitchOn, CameraIndex))
		{
			CurrentCameraIndex = CameraIndex;
		}
		CameraToSwitchOn->SetActive(true);
	}
}

void APlayerVehicle::RotateSteeringWheelToMatchWheels()
{
	if (GetMesh())
	{
		float WheelYaw = GetMesh()->GetSocketTransform(FName("suspension_front_right"), ERelativeTransformSpace::RTS_ParentBoneSpace).Rotator().Yaw;
		if (WheelYaw < -120)
		{
			WheelYaw += 180;
		}
		else
		{
			if (WheelYaw > 120)
			{
				WheelYaw -= 180;
			}
		}
		const float SteeringWheelRoatation = FMath::GetMappedRangeValueClamped(FVector2D(-55.0f, 55.0f), FVector2D(-90.0f, 90.0f), WheelYaw);

		if (SteeringWheel)
		{
			SteeringWheel->SetRelativeRotation(FRotator(0.f, 0.f, SteeringWheelRoatation));
		}
	}
}

void APlayerVehicle::RaceFinished()
{
	Super::RaceFinished();

	if (APlayerControllerBase* const PlayerController = Cast<APlayerControllerBase>(GetController()))
	{
		PlayerController->RaceFinished();
	}
}

void APlayerVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateSteeringWheelToMatchWheels();
}