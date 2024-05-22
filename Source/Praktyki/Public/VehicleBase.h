// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "VehicleBase.generated.h"

struct FInputActionValue;

UCLASS()
class PRAKTYKI_API AVehicleBase : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	AVehicleBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LapFinished();

	void CheckpointReached(AActor* const CheckpointReached);

	uint32 GetNumberOfCheckpointsReached() const;

	uint32 GetCurrentLap() const;

	void RaceFinished();

	void RaceStarts();

	TArray<uint32> GetLapTimes() const;
protected:
	virtual void BeginPlay() override;

private:
	void Steering(const FInputActionValue& Value);

	void Throttle(const FInputActionValue& Value);

	void Brake(const FInputActionValue& Value);

	void StartHandbrake(const FInputActionValue& Value);
	void StopHandbrake(const FInputActionValue& Value);

public:

protected:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* SteeringAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ThrottleAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* BrakeAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* HandbrakeAction;

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
	UStaticMeshComponent* Wiper;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArm;

private:
	TArray<AActor*>VisitedCheckpoints;

	uint32 CurrentLap = 1;

	uint32 CurrentLapTime = 0; // Hundredths of second

	TArray<uint32>LapTimes;

	FTimerHandle LapTimer;
};
