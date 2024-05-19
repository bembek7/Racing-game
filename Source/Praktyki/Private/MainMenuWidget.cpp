// Copyright 2023 Teyon. All Rights Reserved.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "PlayerControllerBase.h"

void UMainMenuWidget::NativeConstruct()
{
	FScriptDelegate StartDelegate;
	StartDelegate.BindUFunction(this, FName("StartGame"));
	if (StartButton)
	{
		StartButton->OnClicked.AddUnique(StartDelegate);
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
