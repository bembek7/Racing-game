// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 *
 */
class UButton;
class USpinBox;
class UComboBoxString;

UCLASS()
class PRAKTYKI_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void NumberOfLapsChanged();

	UFUNCTION()
	void RaceModeChanged();

	UFUNCTION()
	void QuitGame() const;

	UFUNCTION()
	void LiveryColorChanged() const;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USpinBox* NumberOfLaps;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UComboBoxString* LiveryColor;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UComboBoxString* RaceMode;
};
