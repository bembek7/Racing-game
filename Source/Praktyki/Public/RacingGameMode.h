// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameMode.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API ARacingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void VehicleCrossedFinishLine(class AVehicleBase* const VehicleThatCrossed) const;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>CheckpointClass;

	uint32 NumberOfCheckpoints = 0;
};
