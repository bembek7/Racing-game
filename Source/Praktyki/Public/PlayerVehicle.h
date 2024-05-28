// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VehicleBase.h"
#include "PlayerVehicle.generated.h"

/**
 *
 */
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PRAKTYKI_API APlayerVehicle : public AVehicleBase
{
	GENERATED_BODY()

public:
	APlayerVehicle();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void RaceFinished() override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void Steering(const FInputActionValue& Value);

	void Throttle(const FInputActionValue& Value);

	void Brake(const FInputActionValue& Value);

	void StartHandbrake(const FInputActionValue& Value);
	void StopHandbrake(const FInputActionValue& Value);

	void SwitchToNextCamera();

	void SwitchToCameraFromAbove();
	void SwitchToFrontCamera();
	void SwitchToCarInteriorCamera();
	void SwitchToCamera(class UCameraComponent* const CameraToSwitchOn);

	virtual void ResetVehicle() override;

	void RotateSteeringWheelToMatchWheels();

protected:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* SteeringAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* ThrottleAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* BrakeAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* HandbrakeAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* SwitchToNextCameraAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* SwitchToCameraFromAboveAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* SwitchToFrontCameraAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* SwitchToCarInteriorCameraAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* ResetVehicleAction;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraFromAbove;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CarInteriorCamera;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* FrontCamera;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

private:
	TArray<UCameraComponent*> Cameras;
	uint32 CurrentCameraIndex = 0;
};
