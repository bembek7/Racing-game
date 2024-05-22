// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameMode.generated.h"

UENUM()
enum ERaceMode : uint8 {
	Qualifications,
	Race
};

UCLASS()
class PRAKTYKI_API ARacingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARacingGameMode();

	void VehicleCrossedFinishLine(class AVehicleBase* const VehicleThatCrossed) const;

	bool IsNumberOfLapsChangable() const;

	FString GetRaceModeName() const;

	uint32 GetNumberOfLaps() const;

	void GetAllRaceModesNames(TArray<FString>& OutNamesArray) const;

	void SetNumberOfLaps(const uint32 NewNumberOfLaps);

	void SetRaceModeFromString(const FString& RaceModeName);

	void RaceStarts();

	uint32 GetRaceTime() const;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> CheckpointClass;

private:
	FTimerHandle RaceTimer;

	uint32 NumberOfCheckpoints = 0;

	ERaceMode CurrentRaceMode = ERaceMode::Qualifications;

	uint32 NumberOfLaps = 1;

	TMap<ERaceMode, FString> RaceModesNamesMap;

	uint32 CurrentRaceTime = 0; //Hundredths of second
};
