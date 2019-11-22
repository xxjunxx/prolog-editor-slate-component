// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/SlateCore/Public/Styling/SlateStyle.h"

/**
 * 
 */
class  FPrologEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static const ISlateStyle& Get();

	static const FName& GetStyleSetName();

private:

	/** Singleton instances of this style. */
	static TSharedPtr< class FSlateStyleSet > StyleSet;
};
