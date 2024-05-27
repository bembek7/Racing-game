// Copyright 2023 Teyon. All Rights Reserved.

#include "InRaceWidget.h"
#include "PlayerControllerBase.h"
#include "Components/TextBlock.h"
#include "VehicleBase.h"
#include "RacingGameMode.h"
#include "Kismet/GameplayStatics.h"

void UInRaceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LapProgressText->SetVisibility(ESlateVisibility::Collapsed);
	RaceTimerText->SetVisibility(ESlateVisibility::Collapsed);
	SurvivalTimeRemainingText->SetVisibility(ESlateVisibility::Collapsed);

	FScriptDelegate OnVisibilityChangedDelegate;
	OnVisibilityChangedDelegate.BindUFunction(this, FName("VisibilityChanged"));
	OnVisibilityChanged.AddUnique(OnVisibilityChangedDelegate);
}

FText UInRaceWidget::GetCountDownText() const
{
	if (APlayerControllerBase* const OwningController = Cast<APlayerControllerBase>(GetOwningPlayer()))
	{
		const int32 SecondsLeft = FMath::CeilToInt32(OwningController->GetTimeLeftInCountdown());
		return FText::FromString(FString::FromInt(SecondsLeft));
	}
	return FText();
}

FText UInRaceWidget::GetLapProgressText() const
{
	if (APlayerController* const OwningController = GetOwningPlayer())
	{
		if (AVehicleBase* const OwningVehicle = Cast<AVehicleBase>(OwningController->GetPawn()))
		{
			if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				const uint32 VehicleCurrentLap = OwningVehicle->GetCurrentLap();
				const uint32 NumberOfLaps = GameMode->GetNumberOfLaps();
				return FText::FromString(FString::Printf(TEXT("%d/%d"), VehicleCurrentLap, NumberOfLaps));
			}
		}
	}
	return FText();
}

FText UInRaceWidget::TimeToText(const uint32 TimeInHundredthsOfSeconds) const
{
	const uint32 HundredthsOfSeconds = TimeInHundredthsOfSeconds % 10;
	const uint32 TensOfHundredthsOfSeconds = TimeInHundredthsOfSeconds % 100 / 10;
	const uint32 Seconds = TimeInHundredthsOfSeconds % 1000 / 100;
	const uint32 TensOfSeconds = TimeInHundredthsOfSeconds % 6000 / 1000;
	const uint32 Minutes = TimeInHundredthsOfSeconds % 360000 / 6000;
	const uint32 TensOfMinutes = TimeInHundredthsOfSeconds / 60000;
	const FString Time = FString::Printf(TEXT("%d%d:%d%d:%d%d"), TensOfMinutes, Minutes, TensOfSeconds, Seconds, TensOfHundredthsOfSeconds, HundredthsOfSeconds);
	return FText::FromString(Time);
}

FText UInRaceWidget::GetRaceTimerText() const
{
	if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		const uint32 RaceTime = GameMode->GetRaceTime();
		return TimeToText(RaceTime);
	}
	return FText();
}

FText UInRaceWidget::GetSurvivalRemainingTimeText() const
{
	if (APlayerController* const OwningController = GetOwningPlayer())
	{
		if (AVehicleBase* const OwningVehicle = Cast<AVehicleBase>(OwningController->GetPawn()))
		{
			return TimeToText(OwningVehicle->GetSurvivalRemainingTime());
		}
	}
	return FText();
}

void UInRaceWidget::RaceStarted()
{
	if (CountDownText)
	{
		CountDownText->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (LapProgressText)
	{
		LapProgressText->SetVisibility(ESlateVisibility::Visible);
	}
	if (RaceTimerText)
	{
		RaceTimerText->SetVisibility(ESlateVisibility::Visible);
	}
	if (SurvivalTimeRemainingText)
	{
		if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			if (GameMode->IsInSurvivalMode())
			{
				SurvivalTimeRemainingText->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void UInRaceWidget::VisibilityChanged()
{
	if (CountDownText)
	{
		CountDownText->SetVisibility(ESlateVisibility::Visible);
	}
	if (LapProgressText)
	{
		LapProgressText->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (RaceTimerText)
	{
		RaceTimerText->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (SurvivalTimeRemainingText)
	{
		SurvivalTimeRemainingText->SetVisibility(ESlateVisibility::Collapsed);
	}
}