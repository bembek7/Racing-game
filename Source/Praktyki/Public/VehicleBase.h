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
	// Sets default values for this pawn's properties
	AVehicleBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LapStarted();

	void CheckpointReached(AActor* const CheckpointReached);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Handles steering input */
	void Steering(const FInputActionValue& Value);

	/** Handles throttle input */
	void Throttle(const FInputActionValue& Value);

	/** Handles brake input */
	void Brake(const FInputActionValue& Value);

public:

protected:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* SteeringAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ThrottleAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* BrakeAction;


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

	uint32 CurrentLap = 0;

	uint32 NrOfCheckpointsPassed = 0;

};
