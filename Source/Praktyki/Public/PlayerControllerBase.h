// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 *
 */
class UInputMappingContext;
class UInRaceWidget;

UCLASS()
class PRAKTYKI_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	void StartCountDown();

	float GetTimeLeftInCountdown() const;

	void RaceFinished();

	void ShowMainMenu();

protected:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void StartRace();

protected:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget>MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget>InRaceWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget>RaceFinishedWidgetClass;

private:
	const float TimeToRaceStart = 3.f;
	FTimerHandle CountDownHandle;
	UInRaceWidget* InRaceWidget;
	UUserWidget* MainMenuWidget;
	UUserWidget* RaceFinishedWidget;
};
