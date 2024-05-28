// Copyright 2023 Teyon. All Rights Reserved.

#include "VehicleBase.h"
#include "Components/SceneCaptureComponent2D.h"
#include "RacingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ChaosVehicleMovementComponent.h"

AVehicleBase::AVehicleBase()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	PartsBoneNames.Emplace(Body, FName("SK_Porsche_911_Gt3_R1"));

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Front Bumper"));
	PartsBoneNames.Emplace(FrontBumper, FName("bumper_front"));

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Door"));
	PartsBoneNames.Emplace(LeftDoor, FName("door_left"));

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Door"));
	PartsBoneNames.Emplace(RightDoor, FName("door_right"));

	RearBumper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Rear Bumper"));
	PartsBoneNames.Emplace(RearBumper, FName("bumper_rear"));

	RearBoot = CreateDefaultSubobject<UStaticMeshComponent>(FName("Rear Boot"));
	PartsBoneNames.Emplace(RearBoot, FName("boot_rear"));

	BackSpoiler = CreateDefaultSubobject<UStaticMeshComponent>(FName("Back Spoiler"));
	PartsBoneNames.Emplace(BackSpoiler, FName("spoiler_back"));

	LeftWingMirror = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Wing Mirror"));
	PartsBoneNames.Emplace(LeftWingMirror, FName("wing_mirror_left"));

	RightWingMirror = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Wing Mirror"));
	PartsBoneNames.Emplace(RightWingMirror, FName("wing_mirror_right"));

	LeftBackWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Back Wheel"));
	PartsBoneNames.Emplace(LeftBackWheel, FName("suspension_back_left"));

	RightBackWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Back Wheel"));
	PartsBoneNames.Emplace(RightBackWheel, FName("suspension_back_right"));

	LeftFrontWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Front Wheel"));
	PartsBoneNames.Emplace(LeftFrontWheel, FName("suspension_front_left"));

	RightFrontWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Front Wheel"));
	PartsBoneNames.Emplace(RightFrontWheel, FName("suspension_front_right"));

	EngineComponents = CreateDefaultSubobject<UStaticMeshComponent>(FName("Engine Components"));
	PartsBoneNames.Emplace(EngineComponents, FName("SK_Porsche_911_Gt3_R1"));

	ExteriorInteriorWindows = CreateDefaultSubobject<UStaticMeshComponent>(FName("Exterior Interior Windows"));
	PartsBoneNames.Emplace(ExteriorInteriorWindows, FName("SK_Porsche_911_Gt3_R1"));

	LeftFender = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Fender"));
	PartsBoneNames.Emplace(LeftFender, FName("fender_left"));

	RightFender = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Fender"));
	PartsBoneNames.Emplace(RightFender, FName("fender_right"));

	FrontHood = CreateDefaultSubobject<UStaticMeshComponent>(FName("Front Hood"));
	PartsBoneNames.Emplace(FrontHood, FName("hood_front"));

	LeftRearCaliper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Rear Caliper"));
	PartsBoneNames.Emplace(LeftRearCaliper, FName("suspension_back_left"));

	RightRearCaliper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Rear Caliper"));
	PartsBoneNames.Emplace(RightRearCaliper, FName("suspension_back_right"));

	LeftFrontCaliper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Front Caliper"));
	PartsBoneNames.Emplace(LeftFrontCaliper, FName("suspension_front_left"));

	RightFrontCaliper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Front Caliper"));
	PartsBoneNames.Emplace(RightFrontCaliper, FName("suspension_front_right"));

	Interior = CreateDefaultSubobject<UStaticMeshComponent>(FName("Interior"));
	PartsBoneNames.Emplace(Interior, FName("SK_Porsche_911_Gt3_R1"));

	Net = CreateDefaultSubobject<UStaticMeshComponent>(FName("Net"));
	PartsBoneNames.Emplace(Net, FName("SK_Porsche_911_Gt3_R1"));

	BrakePedal = CreateDefaultSubobject<UStaticMeshComponent>(FName("Brake Pedal"));
	PartsBoneNames.Emplace(BrakePedal, FName("SK_Porsche_911_Gt3_R1"));

	AccelerationPedal = CreateDefaultSubobject<UStaticMeshComponent>(FName("Acceleration Pedal"));
	PartsBoneNames.Emplace(AccelerationPedal, FName("SK_Porsche_911_Gt3_R1"));

	LeftRearBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Rear Brake Disc"));
	PartsBoneNames.Emplace(LeftRearBrakeDisc, FName("suspension_back_left"));

	RightRearBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Rear Brake Disc"));
	PartsBoneNames.Emplace(RightRearBrakeDisc, FName("suspension_back_right"));

	LeftFrontBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Front Brake Disc"));
	PartsBoneNames.Emplace(LeftFrontBrakeDisc, FName("suspension_front_left"));

	RightFrontBrakeDisc = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Front Brake Disc"));
	PartsBoneNames.Emplace(RightFrontBrakeDisc, FName("suspension_front_right"));

	RearDiffuser = CreateDefaultSubobject<UStaticMeshComponent>(FName("Rear Diffuser"));
	PartsBoneNames.Emplace(RearDiffuser, FName("diffuser_back"));

	SeatNetClamps = CreateDefaultSubobject<UStaticMeshComponent>(FName("Seat Net Clamps"));
	PartsBoneNames.Emplace(SeatNetClamps, FName("SK_Porsche_911_Gt3_R1"));

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Steering Wheel"));
	PartsBoneNames.Emplace(SteeringWheel, FName("SK_Porsche_911_Gt3_R1"));

	Wiper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wiper"));
	PartsBoneNames.Emplace(Wiper, FName("hood_front"));

	CockpitConsole = CreateDefaultSubobject<UStaticMeshComponent>(FName("Cockpit Console"));
	PartsBoneNames.Emplace(CockpitConsole, FName("SK_Porsche_911_Gt3_R1"));

	for (auto& Part : PartsBoneNames)
	{
		Part.Key->SetupAttachment(GetMesh(), Part.Value);
	}

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
		if (Body)
		{
			LiveryParts.Add(FLiveryPart(Body, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (FrontBumper)
		{
			LiveryParts.Add(FLiveryPart(FrontBumper, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (LeftDoor)
		{
			LiveryParts.Add(FLiveryPart(LeftDoor, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (RightDoor)
		{
			LiveryParts.Add(FLiveryPart(RightDoor, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (RearBumper)
		{
			LiveryParts.Add(FLiveryPart(RearBumper, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (RearBoot)
		{
			LiveryParts.Add(FLiveryPart(RearBoot, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (BackSpoiler)
		{
			LiveryParts.Add(FLiveryPart(BackSpoiler, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (LeftWingMirror)
		{
			LiveryParts.Add(FLiveryPart(LeftWingMirror, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (RightWingMirror)
		{
			LiveryParts.Add(FLiveryPart(RightWingMirror, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (LeftFender)
		{
			LiveryParts.Add(FLiveryPart(LeftFender, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (RightFender)
		{
			LiveryParts.Add(FLiveryPart(RightFender, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
		if (FrontHood)
		{
			LiveryParts.Add(FLiveryPart(FrontHood, UMaterialInstanceDynamic::Create(OrignalLiveryMaterial, this)));
		}
	}

	for (const auto& LiveryPart : LiveryParts)
	{
		if (LiveryPart.Mesh && LiveryPart.DynamicMaterial)
		{
			LiveryPart.Mesh->SetMaterialByName(LiverySlotName, LiveryPart.DynamicMaterial);
		}
	}

	FScriptDelegate OnHitDelegate;
	OnHitDelegate.BindUFunction(this, FName("OnVehicleHit"));
	GetMesh()->OnComponentHit.AddUnique(OnHitDelegate);
}

void AVehicleBase::ResetVehicle()
{
	const FVector ResetLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);

	FRotator ResetRotation = GetActorRotation();
	ResetRotation.Pitch = 0.0f;
	ResetRotation.Roll = 0.0f;

	TeleportTo(ResetLocation, ResetRotation);
	GetVehicleMovement()->StopMovementImmediately();
}

void AVehicleBase::OnVehicleHit(UPrimitiveComponent* const HitComponent, AActor* const OtherActor, UPrimitiveComponent* const OtherComp, const FVector& NormalImpuls, const FHitResult& Hit)
{
	const FVector Velocity = GetVelocity();

	const float HitStrength = FMath::Abs(FVector::DotProduct(Velocity, Hit.ImpactNormal)); // It's definitely not ideal, but it have to do for now

	const FVector TraceStart = Hit.Location;

	TArray<AActor*> ActorsToIgnore;

	TArray<FHitResult> TraceHitResults;

	const float TraceRadius = 35.f;

	const bool LiveryHit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), TraceStart, TraceStart, TraceRadius, UEngineTypes::ConvertToTraceType(ECC_Camera), false,
		ActorsToIgnore, EDrawDebugTrace::None, TraceHitResults, false);

	if (LiveryHit)
	{
		for (const auto& HitResult : TraceHitResults)
		{
			if (HitResult.GetActor() == this)
			{
				for (auto& LiveryPart : LiveryParts)
				{
					if (LiveryPart.Mesh == HitResult.Component)
					{
						DamagePart(LiveryPart, HitStrength);
						break;
					}
				}
			}
		}
	}
}

void AVehicleBase::DamagePart(FLiveryPart& HitPart, const float HitStrength)
{
	if (HitPart.CurrentHealth > 0)
	{
		const float HitDamage = HitStrength * LiveryDamageFromHitStrengthMultiplier;
		HitPart.CurrentHealth -= HitDamage;
		if (HitPart.CurrentHealth <= 0)
		{
			if (HitPart.Mesh && HitPart.Mesh != Body)
			{
				HitPart.Mesh->SetSimulatePhysics(true);
			}
		}
		else
		{
			const float MaterialDamageValue = 1 - HitPart.CurrentHealth / HitPart.MaxHealth;
			if (HitPart.DynamicMaterial)
			{
				HitPart.DynamicMaterial->SetScalarParameterValue(FName("DamageValue"), MaterialDamageValue);
			}
		}
	}
}

void AVehicleBase::LapFinished()
{
	++CurrentLap;
	VisitedCheckpoints.Empty();
	LapTimes.Add(CurrentLapTime);
	CurrentLapTime = 0;

	if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (GameMode->IsInSurvivalMode())
		{
			SurvivalRemainingTime += GameMode->GetSurvivalCheckpointIncrement();
		}
	}
}

void AVehicleBase::CheckpointReached(AActor* const CheckpointReached)
{
	if (!VisitedCheckpoints.Contains(CheckpointReached))
	{
		VisitedCheckpoints.Add(CheckpointReached);

		if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			if (GameMode->IsInSurvivalMode())
			{
				SurvivalRemainingTime += GameMode->GetSurvivalCheckpointIncrement();
			}
		}
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

	GetWorldTimerManager().ClearTimer(SurvivalTimer);
	GetWorldTimerManager().ClearTimer(LapTimer);
}

void AVehicleBase::RaceStarts()
{
	bBlockEngineInput = false;

	VisitedCheckpoints.Empty();
	LapTimes.Empty();
	CurrentLap = 1;

	CurrentLapTime = 0;
	GetWorldTimerManager().ClearTimer(LapTimer);
	GetWorldTimerManager().SetTimer(LapTimer, [this]() { ++CurrentLapTime; }, 0.01f, true); // Could just set the timer, but I think it's easier this way

	// Survival mode stuff
	if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (GameMode->IsInSurvivalMode())
		{
			StartSurvivalTimer(GameMode->GetSurvivalStartingTime());
		}
	}
}

void AVehicleBase::StartSurvivalTimer(const float StartingTime)
{
	SurvivalRemainingTime = StartingTime;
	GetWorldTimerManager().ClearTimer(SurvivalTimer);
	GetWorldTimerManager().SetTimer(SurvivalTimer, [this]()
	{
		--SurvivalRemainingTime;
		if (SurvivalRemainingTime <= 0)
		{
			RaceFinished();
		}
	}, 0.01f, true); // Could just set the timer, but I think it's easier this way

}

TArray<uint32> AVehicleBase::GetLapTimes() const
{
	return LapTimes;
}

void AVehicleBase::PrepareForRace(const FTransform& StartingPosition)
{
	ResetLiveryParts();
	TeleportToStartingPosition(StartingPosition);
}

void AVehicleBase::TeleportToStartingPosition(const FTransform& StartingPosition)
{
	TeleportTo(StartingPosition.GetLocation(), StartingPosition.Rotator());
	GetVehicleMovement()->StopMovementImmediately();
}

void AVehicleBase::ResetLiveryParts()
{
	for (auto& LiveryPart : LiveryParts)
	{
		LiveryPart.CurrentHealth = LiveryPart.MaxHealth;
		if (LiveryPart.Mesh)
		{
			LiveryPart.Mesh->SetSimulatePhysics(false);
			
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
			LiveryPart.Mesh->AttachToComponent(GetMesh(), AttachmentRules, *PartsBoneNames.Find(LiveryPart.Mesh));
		}
		if (LiveryPart.DynamicMaterial)
		{
			LiveryPart.DynamicMaterial->SetScalarParameterValue(FName("DamageValue"), 0.f);
		}
	}
}

void AVehicleBase::SetAlbedoColorOnLiveryMaterial(const FString& NewLiveryColor)
{
	const ELiveryColor ChosenColor = *LiveryColorsStringMap.Find(NewLiveryColor);

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

	if (ChosenTexture)
	{
		for (const auto& LiveryPart : LiveryParts)
		{
			if (LiveryPart.DynamicMaterial)
			{
				LiveryPart.DynamicMaterial->SetTextureParameterValue(FName("Albedo"), ChosenTexture);
			}
		}
	}
}

int32 AVehicleBase::GetSurvivalRemainingTime() const
{
	return SurvivalRemainingTime;
}