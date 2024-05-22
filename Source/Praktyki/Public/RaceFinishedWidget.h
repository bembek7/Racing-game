// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceFinishedWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API URaceFinishedWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:

private:
	UFUNCTION()
	void GoToMainMenu();

	UFUNCTION()
	void PlayAgain();

	void UpdateLapTimesList();

	UFUNCTION()
	void VisibilityChanged();

	FText TimeToText(const uint32 TimeInHundredthsOfSeconds) const;

	UFUNCTION()
	void QuitGame() const;
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* GoToMainMenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* PlayAgainButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UScrollBox* LapTimes;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitButton;
};
