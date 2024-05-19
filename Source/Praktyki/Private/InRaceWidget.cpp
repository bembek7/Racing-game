// Copyright 2023 Teyon. All Rights Reserved.

#include "InRaceWidget.h"
#include "PlayerControllerBase.h"
#include "Components/TextBlock.h"
#include "VehicleBase.h"

void UInRaceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentLapText->SetVisibility(ESlateVisibility::Collapsed);
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

FText UInRaceWidget::GetCurrentLapText() const
{
	if (APlayerControllerBase* const OwningController = Cast<APlayerControllerBase>(GetOwningPlayer()))
	{
		if (AVehicleBase* const OwningVehicle = Cast<AVehicleBase>(OwningController->GetPawn()))
		{
			const uint32 VehicleCurrentLap = OwningVehicle->GetCurrentLap();
			return FText::FromString(FString::FromInt(VehicleCurrentLap));
		}
	}
	return FText();
}

void UInRaceWidget::RaceStarted()
{
	CountDownText->SetVisibility(ESlateVisibility::Collapsed);
	CurrentLapText->SetVisibility(ESlateVisibility::Visible);
}