// Copyright 2023 Teyon. All Rights Reserved.


#include "PlayerControllerBase.h"
#include "EnhancedInputSubsystems.h"

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}
