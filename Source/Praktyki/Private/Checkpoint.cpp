// Copyright 2023 Teyon. All Rights Reserved.

#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "VehicleBase.h"

ACheckpoint::ACheckpoint()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("Box Collider"));
	SetRootComponent(BoxCollider);
}

void ACheckpoint::BeginPlay()
{
	FScriptDelegate OnBeginOverlapDelegate;
	OnBeginOverlapDelegate.BindUFunction(this, FName("ActorPassedTheCheckpoint"));
	BoxCollider->OnComponentBeginOverlap.AddUnique(OnBeginOverlapDelegate);
}

void ACheckpoint::ActorPassedTheCheckpoint(UPrimitiveComponent* const OverlappedComp, AActor* const OtherActor, UPrimitiveComponent* const OtherComp)
{
	if (AVehicleBase* const VehicleThatPassed = Cast<AVehicleBase>(OtherActor))
	{
		VehicleThatPassed->CheckpointReached(this);
	}
}