// Copyright 2023 Teyon. All Rights Reserved.

#include "RacingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "VehicleBase.h"
#include "StartingPosition.h"

ARacingGameMode::ARacingGameMode()
{
	RaceModesNamesMap.Emplace(ERaceMode::Qualifications, TEXT("Qualifications"));
	RaceModesNamesMap.Emplace(ERaceMode::Race, TEXT("Race"));
	RaceModesNamesMap.Emplace(ERaceMode::Survival, TEXT("Survival"));
}

void ARacingGameMode::BeginPlay()
{
	TArray<AActor*>CheckpointsFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CheckpointClass, CheckpointsFound);
	NumberOfCheckpoints = CheckpointsFound.Num();

	GenerateStartingPostionsForVehicles();
}

void ARacingGameMode::GenerateStartingPostionsForVehicles()
{
	TArray<AActor*>StartingPositions;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStartingPosition::StaticClass(), StartingPositions);
	TArray<AActor*>Vehicles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVehicleBase::StaticClass(), Vehicles);
	uint32 VehicleIndex = 0;
	for (auto const StartingPosition : StartingPositions)
	{
		if (VehicleIndex == Vehicles.Num())
		{
			break;
		}
		if (AStartingPosition* const StartingPositionCasted = Cast<AStartingPosition>(StartingPosition))
		{
			if (StartingPositionCasted->GetStartingPlace() <= Vehicles.Num())
			{
				if (Vehicles[VehicleIndex])
				{
					VehiclesStartingPostions.Add(Vehicles[VehicleIndex], StartingPositionCasted->GetActorTransform());
					++VehicleIndex;
				}
			}
		}
	}
}

void ARacingGameMode::VehicleCrossedFinishLine(AVehicleBase* const VehicleThatCrossed) const
{
	if (VehicleThatCrossed && VehicleThatCrossed->GetNumberOfCheckpointsReached() == NumberOfCheckpoints)
	{
		VehicleThatCrossed->LapFinished();
		if (VehicleThatCrossed->GetCurrentLap() > NumberOfLaps)
		{
			VehicleThatCrossed->RaceFinished();
		}
	}
}

bool ARacingGameMode::IsNumberOfLapsChangable() const
{
	if (CurrentRaceMode == ERaceMode::Qualifications || CurrentRaceMode == ERaceMode::Survival)
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
	if (CurrentRaceMode == ERaceMode::Survival)
	{
		NumberOfLaps = 10;
	}
}

void ARacingGameMode::RaceStarts()
{
	CurrentRaceTime = 0;
	GetWorldTimerManager().ClearTimer(RaceTimer);
	GetWorldTimerManager().SetTimer(RaceTimer, [this]() { ++CurrentRaceTime; }, 0.01f, true); // Could just set the timer, but I think it's easier this way

	// We are calling it on every vehicle in case there are more vehicles in the future
	TArray<AActor*>Vehicles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVehicleBase::StaticClass(), Vehicles);
	for (auto const Vehicle : Vehicles)
	{
		if (AVehicleBase* const VehicleFound = Cast<AVehicleBase>(Vehicle))
		{
			VehicleFound->RaceStarts();
		}
	}
}

uint32 ARacingGameMode::GetRaceTime() const
{
	return CurrentRaceTime;
}

void ARacingGameMode::PrepareVehicles()
{
	for (const auto& VehiclePostion : VehiclesStartingPostions)
	{
		if (AVehicleBase* const Vehicle = Cast<AVehicleBase>(VehiclePostion.Key))
		{
			Vehicle->PrepareForRace(VehiclePostion.Value);
		}
	}
}

bool ARacingGameMode::IsInSurvivalMode() const
{
	return CurrentRaceMode == ERaceMode::Survival;
}

uint32 ARacingGameMode::GetSurvivalStartingTime() const
{
	return SurvivalStartingTime;
}

uint32 ARacingGameMode::GetSurvivalCheckpointIncrement() const
{
	return SurvivalCheckpointIncrement;
}