// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PrologStyle.h"

class FPrologCommands : public TCommands<FPrologCommands>
{
public:

	FPrologCommands()
		: TCommands<FPrologCommands>(TEXT("Prolog"), NSLOCTEXT("Contexts", "Prolog", "Prolog Plugin"), NAME_None, FPrologStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};