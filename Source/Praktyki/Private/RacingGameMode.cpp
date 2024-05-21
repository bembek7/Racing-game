// Copyright 2023 Teyon. All Rights Reserved.

#include "RacingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "VehicleBase.h"


ARacingGameMode::ARacingGameMode()
{
	RaceModesNamesMap.Emplace(ERaceMode::Qualifications, TEXT("Qualifications"));
	RaceModesNamesMap.Emplace(ERaceMode::Race, TEXT("Race"));
}

void ARacingGameMode::VehicleCrossedFinishLine(AVehicleBase* const VehicleThatCrossed) const
{
	UE_LOG(LogTemp, Warning, TEXT("Finish reached"));
	if (VehicleThatCrossed && VehicleThatCrossed->GetNumberOfCheckpointsReached() == NumberOfCheckpoints)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finish reached valid"));
		VehicleThatCrossed->LapFinished();
		if (VehicleThatCrossed->GetCurrentLap() > NumberOfLaps)
		{

		}
	}
}

bool ARacingGameMode::IsNumberOfLapsChangable() const
{
	if (CurrentRaceMode == ERaceMode::Qualifications)
	{
		return false;
	}
	return true;
}

FString ARacingGameMode::GetRaceModeName() const
{
	return *RaceModesNamesMap.Find(CurrentRaceMode);
}

uint32 ARacingGameMode::GetNumberOfLaps() const
{
	return NumberOfLaps;
}

void ARacingGameMode::GetAllRaceModesNames(TArray<FString>& OutNamesArray) const
{
	RaceModesNamesMap.GenerateValueArray(OutNamesArray);
}

void ARacingGameMode::SetNumberOfLaps(const uint32 NewNumberOfLaps)
{
	NumberOfLaps = NewNumberOfLaps;
}

void ARacingGameMode::SetRaceModeFromString(const FString& RaceModeName)
{
	CurrentRaceMode = *RaceModesNamesMap.FindKey(RaceModeName);
	if (CurrentRaceMode == ERaceMode::Qualifications)
	{
		NumberOfLaps = 1;
	}
}

void ARacingGameMode::BeginPlay()
{
	TArray<AActor*>CheckpointsFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CheckpointClass, CheckpointsFound);
	NumberOfCheckpoints = CheckpointsFound.Num();
}