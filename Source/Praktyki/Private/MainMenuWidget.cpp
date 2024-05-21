// Copyright 2023 Teyon. All Rights Reserved.

#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Components/SpinBox.h"
#include "Components/ComboBoxString.h"
#include "PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "RacingGameMode.h"

void UMainMenuWidget::NativeConstruct()
{
	FScriptDelegate StartDelegate;
	StartDelegate.BindUFunction(this, FName("StartGame"));
	if (StartButton)
	{
		StartButton->OnClicked.AddUnique(StartDelegate);
	}

	FScriptDelegate NumberOfLapsChangedDelegate;
	NumberOfLapsChangedDelegate.BindUFunction(this, FName("NumberOfLapsChanged"));
	if (NumberOfLaps)
	{
		NumberOfLaps->OnValueCommitted.AddUnique(NumberOfLapsChangedDelegate);
	}

	FScriptDelegate GameModeChangedDelegate;
	GameModeChangedDelegate.BindUFunction(this, FName("RaceModeChanged"));
	if (RaceMode)
	{
		RaceMode->OnSelectionChanged.AddUnique(GameModeChangedDelegate);
	}

	if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (NumberOfLaps)
		{
			NumberOfLaps->SetIsEnabled(GameMode->IsNumberOfLapsChangable());
			NumberOfLaps->SetValue(GameMode->GetNumberOfLaps());
		}
		if (RaceMode)
		{
			TArray<FString>RaceModesNames;
			GameMode->GetAllRaceModesNames(RaceModesNames);
			for (const auto& RaceModeName : RaceModesNames)
			{
				RaceMode->AddOption(RaceModeName);
			}
			RaceMode->SetSelectedOption(GameMode->GetRaceModeName());
		}
	}
}

void UMainMenuWidget::StartGame()
{
	SetVisibility(ESlateVisibility::Collapsed);
	if (APlayerControllerBase* const OwningController = Cast<APlayerControllerBase>(GetOwningPlayer()))
	{
		OwningController->StartCountDown();
	}
}

void UMainMenuWidget::NumberOfLapsChanged()
{
	if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->SetNumberOfLaps(NumberOfLaps->GetValue());
	}
}

void UMainMenuWidget::RaceModeChanged()
{
	if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->SetRaceModeFromString(RaceMode->GetSelectedOption());
		if (NumberOfLaps)
		{
			NumberOfLaps->SetIsEnabled(GameMode->IsNumberOfLapsChangable());
			NumberOfLaps->SetValue(GameMode->GetNumberOfLaps());
		}
	}
}
