// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Prolog.h"
#include "PrologStyle.h"
#include "PrologCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "SButton.h"
#include "PrologEditorStyle.h"
#include "PLRichTextSyntaxHighlighterTextLayoutMarshaller.h"

static const FName PrologTabName("Prolog");

#define LOCTEXT_NAMESPACE "FPrologModule"

void FPrologModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FPrologEditorStyle::Initialize();
	
	FPrologStyle::Initialize();
	FPrologStyle::ReloadTextures();

	FPrologCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FPrologCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FPrologModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FPrologModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FPrologModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PrologTabName, FOnSpawnTab::CreateRaw(this, &FPrologModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPrologTabTitle", "Prolog"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FPrologModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FPrologStyle::Shutdown();

	FPrologCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PrologTabName);
}

TSharedRef<SDockTab> FPrologModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FPrologModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("Prolog.cpp"))
		);

	TSharedRef<FPLRichTextSyntaxHighlighterTextLayoutMarshaller> RichTextMarshaller = FPLRichTextSyntaxHighlighterTextLayoutMarshaller::Create(
		FPLRichTextSyntaxHighlighterTextLayoutMarshaller::FSyntaxTextStyle()
	);

	HorizontalScrollbar =
		SNew(SScrollBar)
		.Orientation(Orient_Horizontal)
		.Thickness(FVector2D(10.0f, 10.0f));

	VerticalScrollbar =
		SNew(SScrollBar)
		.Orientation(Orient_Vertical)
		.Thickness(FVector2D(10.0f, 10.0f));
	
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!

			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.Padding(1.0f)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.BorderBackgroundColor(FSlateColor(FLinearColor::White))
				[
					SAssignNew(PrologText, SMultiLineEditableText)
					.Marshaller(RichTextMarshaller)
					.HScrollBar(HorizontalScrollbar)
					.VScrollBar(VerticalScrollbar)
				]
				
			]
			+ SVerticalBox::Slot()
			.Padding(1.0f)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.BorderBackgroundColor(FSlateColor(FLinearColor::White))
				[
					SAssignNew(ConsoleText, SMultiLineEditableText)
					.HScrollBar(HorizontalScrollbar)
					.VScrollBar(VerticalScrollbar)
				]
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Bottom)
			.FillHeight(0.3f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SButton)
					.OnClicked_Raw(this, &FPrologModule::ClearCode)
					.Content()
					[
						SNew(STextBlock)
						.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 16))
						.Text(FText::FromString(TEXT("Clear")))
					]
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SButton)
					.OnClicked_Raw(this, &FPrologModule::SendCode)
					.Content()
					[
						SNew(STextBlock)
						.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 16))
						.Text(FText::FromString(TEXT("Confirm")))
					]
				]
			]
		];


}

void FPrologModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(PrologTabName);
}

void FPrologModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FPrologCommands::Get().OpenPluginWindow);
}

void FPrologModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FPrologCommands::Get().OpenPluginWindow);
}

FReply FPrologModule::SendCode()
{
	return FReply::Handled();
}

FReply FPrologModule::ClearCode()
{
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPrologModule, Prolog)