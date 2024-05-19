// Copyright 2023 Teyon. All Rights Reserved.


#include "InRaceWidget.h"
#include "PlayerControllerBase.h"
#include "Components/TextBlock.h"

void UInRaceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentLap->SetVisibility(ESlateVisibility::Collapsed);
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
	return FText::FromString(FString::FromInt(0));
}

void UInRaceWidget::RaceStarted()
{
	CountDownText->SetVisibility(ESlateVisibility::Collapsed);
	CurrentLap->SetVisibility(ESlateVisibility::Visible);
}