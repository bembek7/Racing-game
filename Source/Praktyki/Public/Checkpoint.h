// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

class UBoxComponent;

UCLASS()
class PRAKTYKI_API ACheckpoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ActorPassedTheCheckpoint(UPrimitiveComponent* const OverlappedComp, AActor* const OtherActor, UPrimitiveComponent* const OtherComp);

protected:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollider;
};
