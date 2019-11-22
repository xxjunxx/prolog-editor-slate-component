// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PrologCommands.h"

#define LOCTEXT_NAMESPACE "FPrologModule"

void FPrologCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Prolog", "Bring up Prolog window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
