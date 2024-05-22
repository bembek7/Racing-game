// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 *
 */
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
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget>MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget>InRaceWidgetClass;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget>RaceFinishedWidgetClass;

private:
	const float TimeToRaceStart = 3.f;
	FTimerHandle CountDownHandle;
	class UInRaceWidget* InRaceWidget;
	UUserWidget* MainMenuWidget;
	UUserWidget* RaceFinishedWidget;
};
