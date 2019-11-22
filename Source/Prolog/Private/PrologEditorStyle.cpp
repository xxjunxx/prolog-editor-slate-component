// Fill out your copyright notice in the Description page of Project Settings.


#include "PrologEditorStyle.h"
#include "EditorStyleSet.h"
#include "SlateCore.h"
#include "Runtime/SlateCore/Public/Styling/SlateStyle.h"
#include "Runtime/Projects/Public/Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FPrologEditorStyle::StyleSet = nullptr;

//#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

void FPrologEditorStyle::Initialize()
{
	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet("PrologEditor"));

	//StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin("UnrealEnginePython")->GetBaseDir() / TEXT("Resources"));

	//const FSlateFontInfo Consolas10 = TTF_FONT("Font/DroidSansMono", 9);
	
	const FTextBlockStyle NormalText = FTextBlockStyle()
		//.SetFont(Consolas10)
		.SetFont(FSlateFontInfo("Veranda", 9))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetShadowColorAndOpacity(FLinearColor::Black)
		.SetHighlightColor(FLinearColor(0.02f, 0.3f, 0.0f));
		//.SetHighlightShape(BOX_BRUSH("UI/TextBlockHighlightShape", FMargin(3.f / 8.f)));

	// Text editor
	{
		StyleSet->Set("TextEditor.NormalText", NormalText);

		StyleSet->Set("SyntaxHighlight.PY.Normal", FTextBlockStyle(NormalText).SetColorAndOpacity(FLinearColor(FColor(0xffffffff))));// yellow
		StyleSet->Set("SyntaxHighlight.PY.Operator", FTextBlockStyle(NormalText).SetColorAndOpacity(FLinearColor(FColor(0xfff92672)))); // light grey
		StyleSet->Set("SyntaxHighlight.PY.Keyword", FTextBlockStyle(NormalText).SetColorAndOpacity(FLinearColor(FColor(0xfff92672)))); // blue
		StyleSet->Set("SyntaxHighlight.PY.String", FTextBlockStyle(NormalText).SetColorAndOpacity(FLinearColor(FColor(0xffe6db74)))); // pinkish
		StyleSet->Set("SyntaxHighlight.PY.Number", FTextBlockStyle(NormalText).SetColorAndOpacity(FLinearColor(FColor(0xffae81dd)))); // cyan
		StyleSet->Set("SyntaxHighlight.PY.Comment", FTextBlockStyle(NormalText).SetColorAndOpacity(FLinearColor(FColor(0xff75715e)))); // green
		StyleSet->Set("SyntaxHighlight.PY.BuiltIn", FTextBlockStyle(NormalText).SetColorAndOpacity(FLinearColor(FColor(0xff52d9ef)))); // light grey
		StyleSet->Set("SyntaxHighlight.PY.Define", FTextBlockStyle(NormalText).SetColorAndOpacity(FLinearColor(FColor(0xffa6e22a)))); // light grey


		//StyleSet->Set("TextEditor.Border", new BOX_BRUSH("UI/TextEditorBorder", FMargin(4.0f / 16.0f), FLinearColor(0.02f, 0.02f, 0.02f, 1)));

		const FEditableTextBoxStyle EditableTextBoxStyle = FEditableTextBoxStyle()
			.SetBackgroundImageNormal(FSlateNoResource())
			.SetBackgroundImageHovered(FSlateNoResource())
			.SetBackgroundImageFocused(FSlateNoResource())
			.SetBackgroundImageReadOnly(FSlateNoResource());

		StyleSet->Set("TextEditor.EditableTextBox", EditableTextBoxStyle);

		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
	}
}

//#undef BOX_BRUSH

void FPrologEditorStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}

const ISlateStyle& FPrologEditorStyle::Get()
{
	return *(StyleSet.Get());
}

const FName& FPrologEditorStyle::GetStyleSetName()
{
	return StyleSet->GetStyleSetName();
}