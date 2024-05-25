// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:

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
	class UButton* StartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USpinBox* NumberOfLaps;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UComboBoxString* LiveryColor;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UComboBoxString* RaceMode;
};
