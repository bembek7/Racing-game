// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishLine.generated.h"

class UBoxComponent;

UCLASS()
class PRAKTYKI_API AFinishLine : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFinishLine();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ActorCrossedTheLine(UPrimitiveComponent* const OverlappedComp, AActor* const OtherActor, UPrimitiveComponent* const OtherComp) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollider;
};
