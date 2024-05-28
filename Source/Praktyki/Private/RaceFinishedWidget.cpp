// Copyright 2023 Teyon. All Rights Reserved.

#include "RaceFinishedWidget.h"
#include "Components/Button.h"
#include "PlayerControllerBase.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "VehicleBase.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/KismetSystemLibrary.h"

void URaceFinishedWidget::NativeConstruct()
{
	FScriptDelegate GoToMainMenuDelegate;
	GoToMainMenuDelegate.BindUFunction(this, FName("GoToMainMenu"));
	if (GoToMainMenuButton)
	{
		GoToMainMenuButton->OnClicked.AddUnique(GoToMainMenuDelegate);
	}

	FScriptDelegate PlayAgainDelegate;
	PlayAgainDelegate.BindUFunction(this, FName("PlayAgain"));
	if (PlayAgainButton)
	{
		PlayAgainButton->OnClicked.AddUnique(PlayAgainDelegate);
	}

	FScriptDelegate QuitDelegate;
	QuitDelegate.BindUFunction(this, FName("QuitGame"));
	if (QuitButton)
	{
		QuitButton->OnClicked.AddUnique(QuitDelegate);
	}

	FScriptDelegate OnVisibilityChangedDelegate;
	OnVisibilityChangedDelegate.BindUFunction(this, FName("VisibilityChanged"));
	OnVisibilityChanged.AddUnique(OnVisibilityChangedDelegate);
}

void URaceFinishedWidget::GoToMainMenu()
{
	SetVisibility(ESlateVisibility::Collapsed);
	if (APlayerControllerBase* const OwningController = Cast<APlayerControllerBase>(GetOwningPlayer()))
	{
		OwningController->ShowMainMenu();
	}
}

void URaceFinishedWidget::PlayAgain()
{
	SetVisibility(ESlateVisibility::Collapsed);
	if (APlayerControllerBase* const OwningController = Cast<APlayerControllerBase>(GetOwningPlayer()))
	{
		OwningController->StartCountDown();
	}
}

void URaceFinishedWidget::UpdateLapTimesList()
{
	if (LapTimes)
	{
		LapTimes->ClearChildren();
		if (APlayerControllerBase* const OwningController = Cast<APlayerControllerBase>(GetOwningPlayer()))
		{
			if (AVehicleBase* const OwningVehicle = Cast<AVehicleBase>(OwningController->GetPawn()))
			{
				const TArray<uint32> LapTimesList = OwningVehicle->GetLapTimes();
				for (const auto& LapTime : LapTimesList)
				{
					UTextBlock* Entry = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
					LapTimes->AddChild(Entry);
					Entry->SetText(TimeToText(LapTime));
				}
			}
		}
	}
}

void URaceFinishedWidget::VisibilityChanged()
{
	UpdateLapTimesList();
}

FText URaceFinishedWidget::TimeToText(const uint32 TimeInHundredthsOfSeconds) const
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

void URaceFinishedWidget::QuitGame() const
{
	if (APlayerController* OwiningPlayer = GetOwningPlayer())
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), OwiningPlayer, EQuitPreference::Quit, false);
	}
}