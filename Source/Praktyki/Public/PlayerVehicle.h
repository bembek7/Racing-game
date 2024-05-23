// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VehicleBase.h"
#include "PlayerVehicle.generated.h"

/**
 * 
 */
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

	void RotateSteeringWheelToMatchWheels();

protected:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* SteeringAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ThrottleAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* BrakeAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* HandbrakeAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* SwitchToNextCameraAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* SwitchToCameraFromAboveAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* SwitchToFrontCameraAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* SwitchToCarInteriorCameraAction;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraFromAbove;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CarInteriorCamera;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* FrontCamera;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArm;

private:
	TArray<UCameraComponent*> Cameras;
	uint32 CurrentCameraIndex = 0;
};
