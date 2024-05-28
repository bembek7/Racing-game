// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "VehicleBase.generated.h"

struct FInputActionValue;
class USceneCaptureComponent2D;

USTRUCT()
struct FLiveryPart
{
	GENERATED_BODY()

	FLiveryPart() = default;
	FLiveryPart(UStaticMeshComponent* PartMesh, UMaterialInstanceDynamic* PartDynamicMaterial) :
		Mesh(PartMesh),
		DynamicMaterial(PartDynamicMaterial),
		CurrentHealth(MaxHealth)
	{}
	UStaticMeshComponent* Mesh;
	UMaterialInstanceDynamic* DynamicMaterial;
	float MaxHealth = 100.f; // Can't do const in USTRUCT
	float CurrentHealth;
};

UENUM()
enum ELiveryColor : uint8 {
	White,
	Orange,
	Yellow,
	Black,
	Default
};

UCLASS()
class PRAKTYKI_API AVehicleBase : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	AVehicleBase();

	void LapFinished();

	void CheckpointReached(AActor* const CheckpointReached);

	uint32 GetNumberOfCheckpointsReached() const;

	uint32 GetCurrentLap() const;

	virtual void RaceFinished();

	void RaceStarts();

	TArray<uint32> GetLapTimes() const;

	void PrepareForRace(const FTransform& StartingPosition);

	void SetAlbedoColorOnLiveryMaterial(const FString& NewLiveryColor);

	int32 GetSurvivalRemainingTime() const;

protected:
	virtual void BeginPlay() override;

	virtual void ResetVehicle();

private:
	UFUNCTION()
	void OnVehicleHit(UPrimitiveComponent* const HitComponent, AActor* const OtherActor, UPrimitiveComponent* const OtherComp, const FVector& NormalImpuls, const FHitResult& Hit);

	void DamagePart(FLiveryPart& HitPart, const float HitStrength);

	void TeleportToStartingPosition(const FTransform& StartingPosition);

	void ResetLiveryParts();

	void StartSurvivalTimer(const float StartingTime);

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Body;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* FrontBumper;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightDoor;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftDoor;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RearBumper;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RearBoot;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BackSpoiler;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftWingMirror;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightWingMirror;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftBackWheel;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightBackWheel;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftFrontWheel;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightFrontWheel;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* EngineComponents;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ExteriorInteriorWindows;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftFender;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightFender;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* FrontHood;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftRearCaliper;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightRearCaliper;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftFrontCaliper;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightFrontCaliper;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Interior;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Net;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BrakePedal;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* AccelerationPedal;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftRearBrakeDisc;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightRearBrakeDisc;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftFrontBrakeDisc;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightFrontBrakeDisc;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RearDiffuser;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SeatNetClamps;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SteeringWheel;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CockpitConsole;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Wiper;

	UPROPERTY(EditDefaultsOnly)
	USceneCaptureComponent2D* RearMirrorsSceneCapture;

	UPROPERTY(EditDefaultsOnly)
	UTexture* LiveryColorDefault;

	UPROPERTY(EditDefaultsOnly)
	UTexture* LiveryColorWhite;

	UPROPERTY(EditDefaultsOnly)
	UTexture* LiveryColorOrange;

	UPROPERTY(EditDefaultsOnly)
	UTexture* LiveryColorBlack;

	UPROPERTY(EditDefaultsOnly)
	UTexture* LiveryColorYellow;

	bool bBlockEngineInput = true;

	UPROPERTY(EditDefaultsOnly)
	float LiveryDamageFromHitStrengthMultiplier = 0.05f;

private:
	TMap<FString, ELiveryColor> LiveryColorsStringMap;

	TMap<UStaticMeshComponent*, FName> PartsBoneNames;;

	TArray<AActor*> VisitedCheckpoints;

	TArray<FLiveryPart> LiveryParts;

	uint32 CurrentLap = 1;

	uint32 CurrentLapTime = 0; // Hundredths of second

	TArray<uint32>LapTimes;

	FTimerHandle LapTimer;

	FTimerHandle SurvivalTimer;

	int32 SurvivalRemainingTime = 0; // Hundredths of second
};
