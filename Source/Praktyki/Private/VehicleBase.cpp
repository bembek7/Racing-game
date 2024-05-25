// Copyright 2023 Teyon. All Rights Reserved.

#include "VehicleBase.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Components/SceneCaptureComponent2D.h"

AVehicleBase::AVehicleBase()
{
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
	LeftRearBrakeDisc->SetupAttachment(GetMesh(), FName("suspension_back_left"));

	RightRearBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Rear Brake Disc"));
	RightRearBrakeDisc->SetupAttachment(GetMesh(), FName("suspension_back_right"));

	LeftFrontBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Front Brake Disc"));
	LeftFrontBrakeDisc->SetupAttachment(GetMesh(), FName("suspension_front_left"));

	RightFrontBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Front Brake Disc"));
	RightFrontBrakeDisc->SetupAttachment(GetMesh(), FName("suspension_front_right"));

	RearDiffuser = CreateDefaultSubobject<UStaticMeshComponent>(FName("Rear Diffuser"));
	RearDiffuser->SetupAttachment(GetMesh(), FName("diffuser_back"));

	SeatNetClamps = CreateDefaultSubobject<UStaticMeshComponent>(FName("Seat Net Clamps"));
	SeatNetClamps->SetupAttachment(GetMesh(), FName("SK_Porsche_911_Gt3_R1"));

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Steering Wheel"));
	SteeringWheel->SetupAttachment(GetMesh(), FName("hood_front"));

	Wiper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wiper"));
	Wiper->SetupAttachment(GetMesh(), FName("hood_front"));

	RearMirrorsSceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(FName("Rear Mirrors Scene Capture"));
	RearMirrorsSceneCapture->SetupAttachment(GetMesh(), FName("RearMirrorsSceneCapture"));

	LiveryColorsStringMap.Emplace(TEXT("White"), ELiveryColor::White);
	LiveryColorsStringMap.Emplace(TEXT("Orange"), ELiveryColor::Orange);
	LiveryColorsStringMap.Emplace(TEXT("Yellow"), ELiveryColor::Yellow);
	LiveryColorsStringMap.Emplace(TEXT("Black"), ELiveryColor::Black);
	LiveryColorsStringMap.Emplace(TEXT("Default"), ELiveryColor::Default);
}


void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();

	const FName LiverySlotName = FName("Livery");

	UMaterialInterface* const OrignalLiveryMaterial = Body->GetMaterialByName(LiverySlotName);
	if (OrignalLiveryMaterial)
	{
		DynamicLiveryMaterial = UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this);
	}

	if (DynamicLiveryMaterial)
	{
		Body->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		FrontBumper->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		LeftDoor->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		RightDoor->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		RearBumper->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		RearBoot->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		BackSpoiler->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		LeftWingMirror->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		RightWingMirror->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		LeftFender->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		RightFender->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
		FrontHood->SetMaterialByName(LiverySlotName, DynamicLiveryMaterial);
	}
}

void AVehicleBase::LapFinished()
{
	++CurrentLap;
	VisitedCheckpoints.Empty();
	LapTimes.Add(CurrentLapTime);
	CurrentLapTime = 0;
}

void AVehicleBase::CheckpointReached(AActor* const CheckpointReached)
{
	if (!VisitedCheckpoints.Contains(CheckpointReached))
	{
		VisitedCheckpoints.Add(CheckpointReached);
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
	bBlockEngineInput = true;
}

void AVehicleBase::RaceStarts()
{
	bBlockEngineInput = false;

	VisitedCheckpoints.Empty();
	LapTimes.Empty();
	CurrentLap = 1;

	CurrentLapTime = 0;
	LapTimer.Invalidate();
	GetWorldTimerManager().SetTimer(LapTimer, [this]() { ++CurrentLapTime; }, 0.01f, true); // Could just set the timer, but I think it's easier this way
}

TArray<uint32> AVehicleBase::GetLapTimes() const
{
	return LapTimes;
}

void AVehicleBase::TeleportVehicleToStartingPosition(const FTransform& StartingPosition)
{
	TeleportTo(StartingPosition.GetLocation(), StartingPosition.Rotator());
	GetVehicleMovement()->StopMovementImmediately();
}

void AVehicleBase::SetAlbedoColorOnLiveryMaterial(const FString& NewLiveryColor)
{
	const ELiveryColor ChosenColor = *LiveryColorsStringMap.Find(NewLiveryColor);
	
	if(DynamicLiveryMaterial)
	{
		UTexture* ChosenTexture;
		switch (ChosenColor)
		{
		case White:
			ChosenTexture = LiveryColorWhite;
			break;
		case Orange:
			ChosenTexture = LiveryColorOrange;
			break;
		case Yellow:
			ChosenTexture = LiveryColorYellow;
			break;
		case Black:
			ChosenTexture = LiveryColorBlack;
			break;
		default:
			ChosenTexture = LiveryColorDefault;
		}
		if(ChosenTexture)
		{
			DynamicLiveryMaterial->SetTextureParameterValue(FName("Albedo"), ChosenTexture);
		}
	}
}
