// Copyright 2023 Teyon. All Rights Reserved.

#include "VehicleBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <PlayerControllerBase.h>

// Sets default values
AVehicleBase::AVehicleBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	Body->SetupAttachment(GetMesh(), FName("SK_Porsche_911_Gt3_R1"));

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Front Bumper"));
	FrontBumper->SetupAttachment(GetMesh(), FName("bumper_front"));

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Door"));
	LeftDoor->SetupAttachment(GetMesh(), FName("door_left"));

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Door"));
	RightDoor->SetupAttachment(GetMesh(), FName("door_right"));

	RearBumper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Rear Bumper"));
	RearBumper->SetupAttachment(GetMesh(), FName("bumper_rear"));

	RearBoot = CreateDefaultSubobject<UStaticMeshComponent>(FName("Rear Boot"));
	RearBoot->SetupAttachment(GetMesh(), FName("boot_rear"));

	BackSpoiler = CreateDefaultSubobject<UStaticMeshComponent>(FName("Back Spoiler"));
	BackSpoiler->SetupAttachment(GetMesh(), FName("spoiler_back"));

	LeftWingMirror = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Wing Mirror"));
	LeftWingMirror->SetupAttachment(GetMesh(), FName("wing_mirror_left"));

	RightWingMirror = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Wing Mirror"));
	RightWingMirror->SetupAttachment(GetMesh(), FName("wing_mirror_right"));

	LeftBackWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Back Wheel"));
	LeftBackWheel->SetupAttachment(GetMesh(), FName("suspension_back_left"));

	RightBackWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Back Wheel"));
	RightBackWheel->SetupAttachment(GetMesh(), FName("suspension_back_right"));

	LeftFrontWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Front Wheel"));
	LeftFrontWheel->SetupAttachment(GetMesh(), FName("suspension_front_left"));

	RightFrontWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Front Wheel"));
	RightFrontWheel->SetupAttachment(GetMesh(), FName("suspension_front_right"));

	EngineComponents = CreateDefaultSubobject<UStaticMeshComponent>(FName("Engine Components"));
	EngineComponents->SetupAttachment(GetMesh(), FName("SK_Porsche_911_Gt3_R1"));

	ExteriorInteriorWindows = CreateDefaultSubobject<UStaticMeshComponent>(FName("Exterior Interior Windows"));
	ExteriorInteriorWindows->SetupAttachment(GetMesh(), FName("SK_Porsche_911_Gt3_R1"));

	LeftFender = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Fender"));
	LeftFender->SetupAttachment(GetMesh(), FName("fender_left"));

	RightFender = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Fender"));
	RightFender->SetupAttachment(GetMesh(), FName("fender_right"));

	FrontHood = CreateDefaultSubobject<UStaticMeshComponent>(FName("Front Hood"));
	FrontHood->SetupAttachment(GetMesh(), FName("hood_front"));

	LeftRearCaliper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Rear Caliper"));
	LeftRearCaliper->SetupAttachment(GetMesh(), FName("suspension_back_left"));

	RightRearCaliper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Rear Caliper"));
	RightRearCaliper->SetupAttachment(GetMesh(), FName("suspension_back_right"));

	LeftFrontCaliper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Front Caliper"));
	LeftFrontCaliper->SetupAttachment(GetMesh(), FName("suspension_front_left"));

	RightFrontCaliper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Front Caliper"));
	RightFrontCaliper->SetupAttachment(GetMesh(), FName("suspension_front_right"));

	Interior = CreateDefaultSubobject<UStaticMeshComponent>(FName("Interior"));
	Interior->SetupAttachment(GetMesh(), FName("SK_Porsche_911_Gt3_R1"));

	Net = CreateDefaultSubobject<UStaticMeshComponent>(FName("Net"));
	Net->SetupAttachment(GetMesh(), FName("SK_Porsche_911_Gt3_R1"));

	BrakePedal = CreateDefaultSubobject<UStaticMeshComponent>(FName("Brake Pedal"));
	BrakePedal->SetupAttachment(GetMesh(), FName("SK_Porsche_911_Gt3_R1"));

	AccelerationPedal = CreateDefaultSubobject<UStaticMeshComponent>(FName("Acceleration Pedal"));
	AccelerationPedal->SetupAttachment(GetMesh(), FName("SK_Porsche_911_Gt3_R1"));

	LeftRearBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Rear Brake Disc"));
	LeftRearBrakeDisc->SetupAttachment(GetMesh(), FName("wheel_back_left_spin"));

	RightRearBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Rear Brake Disc"));
	RightRearBrakeDisc->SetupAttachment(GetMesh(), FName("wheel_back_right_spin"));

	LeftFrontBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Front Brake Disc"));
	LeftFrontBrakeDisc->SetupAttachment(GetMesh(), FName("wheel_front_left_spin"));

	RightFrontBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Front Brake Disc"));
	RightFrontBrakeDisc->SetupAttachment(GetMesh(), FName("wheel_front_right_spin"));

	RearDiffuser = CreateDefaultSubobject<UStaticMeshComponent>(FName("Rear Diffuser"));
	RearDiffuser->SetupAttachment(GetMesh(), FName("diffuser_back"));

	SeatNetClamps = CreateDefaultSubobject<UStaticMeshComponent>(FName("Seat Net Clamps"));
	SeatNetClamps->SetupAttachment(GetMesh(), FName("SK_Porsche_911_Gt3_R1"));

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("SteeringWheel"));
	SteeringWheel->SetupAttachment(GetMesh(), FName("hood_front"));

	Wiper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wiper"));
	Wiper->SetupAttachment(GetMesh(), FName("hood_front"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("Spring Arm"));
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();
}

void AVehicleBase::Steering(const FInputActionValue& Value)
{
	const float SteeringValue = Value.Get<float>();

	GetVehicleMovement()->SetSteeringInput(SteeringValue);
}

void AVehicleBase::Throttle(const FInputActionValue& Value)
{
	const float ThrottleValue = Value.Get<float>();

	GetVehicleMovement()->SetThrottleInput(ThrottleValue);
}

void AVehicleBase::Brake(const FInputActionValue& Value)
{
	const float BreakValue = Value.Get<float>();

	GetVehicleMovement()->SetBrakeInput(BreakValue);
}

void AVehicleBase::StartHandbrake(const FInputActionValue& Value)
{
	GetVehicleMovement()->SetHandbrakeInput(true);
}

void AVehicleBase::StopHandbrake(const FInputActionValue& Value)
{
	GetVehicleMovement()->SetHandbrakeInput(false);
}
// Called every frame
void AVehicleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (SteeringAction)
		{
			EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &AVehicleBase::Steering);
			EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &AVehicleBase::Steering);
		}

		if (ThrottleAction)
		{
			EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AVehicleBase::Throttle);
			EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AVehicleBase::Throttle);
		}

		if (BrakeAction)
		{
			EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &AVehicleBase::Brake);
			EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AVehicleBase::Brake);
		}

		if(HandbrakeAction)
		{
			EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &AVehicleBase::StartHandbrake);
			EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &AVehicleBase::StopHandbrake);
		}
	}
}

void AVehicleBase::LapFinished()
{
	++CurrentLap;
	VisitedCheckpoints.Empty();
}

void AVehicleBase::CheckpointReached(AActor* const CheckpointReached)
{
	if (!VisitedCheckpoints.Contains(CheckpointReached))
	{
		VisitedCheckpoints.Add(CheckpointReached);
		UE_LOG(LogTemp, Warning, TEXT("Checkpoint reached valid"));
	}
}

uint32 AVehicleBase::GetNumberOfCheckpointsReached() const
{
	return VisitedCheckpoints.Num();
}

uint32 AVehicleBase::GetCurrentLap() const
{
	return CurrentLap;
}

void AVehicleBase::RaceFinished()
{
	if (APlayerControllerBase* const APlayerController = Cast<APlayerControllerBase>(GetController()))
	{
		APlayerController->RaceFinished();
	}
}
