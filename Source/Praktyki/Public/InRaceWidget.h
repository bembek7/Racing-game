// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InRaceWidget.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API UInRaceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	FText GetCountDownText() const;

	UFUNCTION(BlueprintCallable)
	FText GetCurrentLapText() const;

	void RaceStarted();

protected:

private:

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CountDownText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CurrentLapText;
};
