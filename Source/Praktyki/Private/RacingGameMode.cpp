// Copyright 2023 Teyon. All Rights Reserved.

#include "RacingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "VehicleBase.h"

void ARacingGameMode::VehicleCrossedFinishLine(AVehicleBase* const VehicleThatCrossed) const
{
	UE_LOG(LogTemp, Warning, TEXT("Finish reached"));
	if (VehicleThatCrossed && VehicleThatCrossed->GetNumberOfCheckpointsReached() == NumberOfCheckpoints)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finish reached valid"));
		VehicleThatCrossed->LapFinished();
	}
}

void ARacingGameMode::BeginPlay()
{
	TArray<AActor*>CheckpointsFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CheckpointClass, CheckpointsFound);
	NumberOfCheckpoints = CheckpointsFound.Num();
}