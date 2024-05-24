// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartingPosition.generated.h"

UCLASS()
class PRAKTYKI_API AStartingPosition : public AActor
{
	GENERATED_BODY()

public:
	int32 GetStartingPlace() const;

protected:
	UPROPERTY(EditInstanceOnly)
	uint32 StartingPlace;
};
