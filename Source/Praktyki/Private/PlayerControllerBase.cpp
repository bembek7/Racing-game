// Copyright 2023 Teyon. All Rights Reserved.

#include "PlayerControllerBase.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "InRaceWidget.h"
#include "RacingGameMode.h"
#include "Kismet/GameplayStatics.h"

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		MainMenuWidget->AddToPlayerScreen();
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (InRaceWidgetClass)
	{
		InRaceWidget = CreateWidget<UInRaceWidget>(this, InRaceWidgetClass);
		InRaceWidget->AddToPlayerScreen();
		InRaceWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (RaceFinishedWidgetClass)
	{
		RaceFinishedWidget = CreateWidget<UUserWidget>(this, RaceFinishedWidgetClass);
		RaceFinishedWidget->AddToPlayerScreen();
		RaceFinishedWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerControllerBase::StartRace()
{
	InRaceWidget->RaceStarted();

	if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->RaceStarts();
	}
}

void APlayerControllerBase::StartCountDown()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	if (InRaceWidget)
	{
		InRaceWidget->SetVisibility(ESlateVisibility::Visible);
	}
	FTimerDelegate CountDownFinishedDelegate;
	CountDownFinishedDelegate.BindUFunction(this, FName("StartRace"));
	GetWorldTimerManager().SetTimer(CountDownHandle, CountDownFinishedDelegate, TimeToRaceStart, false);

	if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->PrepareVehicles();
	}
}

float APlayerControllerBase::GetTimeLeftInCountdown() const
{
	if (CountDownHandle.IsValid())
	{
		return GetWorldTimerManager().GetTimerRemaining(CountDownHandle);
	}
	return 0.f;
}

void APlayerControllerBase::RaceFinished()
{
	if (InRaceWidget)
	{
		InRaceWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

	if (RaceFinishedWidget)
	{
		RaceFinishedWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerControllerBase::ShowMainMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}