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

private:
	void Steering(const FInputActionValue& Value);

	void Throttle(const FInputActionValue& Value);

	void Brake(const FInputActionValue& Value);

	void StartHandbrake(const FInputActionValue& Value);
	void StopHandbrake(const FInputActionValue& Value);

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
	class UCameraComponent* CameraFromAbove;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CarInteriorCamera;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* FrontCamera;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArm;
};
