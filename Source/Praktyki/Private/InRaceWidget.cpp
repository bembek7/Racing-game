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
	if (APlayerControllerBase* const OwningController = Cast<APlayerControllerBase>(GetOwningPlayer()))
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

void UInRaceWidget::RaceStarted()
{
	CountDownText->SetVisibility(ESlateVisibility::Collapsed);
	LapProgressText->SetVisibility(ESlateVisibility::Visible);
}