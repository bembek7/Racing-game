// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InRaceWidget.generated.h"

/**
 *
 */
class UTextBlock;

UCLASS()
class PRAKTYKI_API UInRaceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void RaceStarted();

protected:
	UFUNCTION(BlueprintCallable)
	FText GetCountDownText() const;

	UFUNCTION(BlueprintCallable)
	FText GetLapProgressText() const;

	UFUNCTION(BlueprintCallable)
	FText GetRaceTimerText() const;

	UFUNCTION(BlueprintCallable)
	FText GetSurvivalRemainingTimeText() const;

private:
	UFUNCTION()
	void VisibilityChanged();

	FText TimeToText(const uint32 TimeInHundredthsOfSeconds) const;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* CountDownText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* LapProgressText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* RaceTimerText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* SurvivalTimeRemainingText;
};
