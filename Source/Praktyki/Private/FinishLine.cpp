// Copyright 2023 Teyon. All Rights Reserved.

#include "FinishLine.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RacingGameMode.h"
#include "VehicleBase.h"

AFinishLine::AFinishLine()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("Box Collider"));
	SetRootComponent(BoxCollider);
}

void AFinishLine::BeginPlay()
{
	FScriptDelegate OnBeginOverlapDelegate;
	OnBeginOverlapDelegate.BindUFunction(this, FName("ActorCrossedTheLine"));
	BoxCollider->OnComponentBeginOverlap.AddUnique(OnBeginOverlapDelegate);
}

void AFinishLine::ActorCrossedTheLine(UPrimitiveComponent* const OverlappedComp, AActor* const OtherActor, UPrimitiveComponent* const OtherComp) const
{
	if (ARacingGameMode* const GameMode = Cast<ARacingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (AVehicleBase* const VehicleThatCrossed = Cast<AVehicleBase>(OtherActor))
		{
			GameMode->VehicleCrossedFinishLine(VehicleThatCrossed);
		}
	}
}