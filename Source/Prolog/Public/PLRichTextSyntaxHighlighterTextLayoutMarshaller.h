// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Styling/SlateTypes.h"
#include "PrologSyntaxTokenizer.h"
#include "Runtime/Slate/Public/Framework/Text/PlainTextLayoutMarshaller.h"
#include "Runtime/Slate/Public/Framework/Text/ITextDecorator.h"
#include "PrologEditorStyle.h"

/**
 * 
 */
class  FPLRichTextSyntaxHighlighterTextLayoutMarshaller : public FPlainTextLayoutMarshaller
{
public:

	struct FSyntaxTextStyle
	{
		FSyntaxTextStyle()
			: NormalTextStyle(FPrologEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.PY.Normal"))
			, OperatorTextStyle(FPrologEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.PY.Operator"))
			, KeywordTextStyle(FPrologEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.PY.Keyword"))
			, StringTextStyle(FPrologEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.PY.String"))
			, NumberTextStyle(FPrologEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.PY.Number"))
			, CommentTextStyle(FPrologEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.PY.Comment"))
			, BuiltInKeywordTextStyle(FPrologEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.PY.BuiltIn"))
			, DefineTextStyle(FPrologEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.PY.Define"))

		{
		}

		FSyntaxTextStyle(const FTextBlockStyle& InNormalTextStyle, const FTextBlockStyle& InOperatorTextStyle, const FTextBlockStyle& InKeywordTextStyle, const FTextBlockStyle& InStringTextStyle, const FTextBlockStyle& InNumberTextStyle, const FTextBlockStyle& InCommentTextStyle, const FTextBlockStyle& InBuiltInKeywordTextStyle, const FTextBlockStyle& InDefineTextStyle)
			: NormalTextStyle(InNormalTextStyle)
			, OperatorTextStyle(InOperatorTextStyle)
			, KeywordTextStyle(InKeywordTextStyle)
			, StringTextStyle(InStringTextStyle)
			, NumberTextStyle(InNumberTextStyle)
			, CommentTextStyle(InCommentTextStyle)
			, BuiltInKeywordTextStyle(InBuiltInKeywordTextStyle)
			, DefineTextStyle(InDefineTextStyle)
		{
		}

		FTextBlockStyle NormalTextStyle;
		FTextBlockStyle OperatorTextStyle;
		FTextBlockStyle KeywordTextStyle;
		FTextBlockStyle StringTextStyle;
		FTextBlockStyle NumberTextStyle;
		FTextBlockStyle CommentTextStyle;
		FTextBlockStyle BuiltInKeywordTextStyle;
		FTextBlockStyle DefineTextStyle;
	};

	static TSharedRef< FPLRichTextSyntaxHighlighterTextLayoutMarshaller > Create(const FSyntaxTextStyle& InSyntaxTextStyle);


public:

	virtual ~FPLRichTextSyntaxHighlighterTextLayoutMarshaller();

	// ITextLayoutMarshaller
	virtual void SetText(const FString& SourceString, FTextLayout& TargetTextLayout) override;
	virtual bool RequiresLiveUpdate() const override;

	void EnableSyntaxHighlighting(const bool bEnable);
	bool IsSyntaxHighlightingEnabled() const;

protected:

	void ParseTokens(const FString& SourceString, FTextLayout& TargetTextLayout, TArray<FPrologSyntaxTokenizer::FTokenizedLine> TokenizedLines);


	/** Tokenizer used to style the text */
	TSharedPtr< FPrologSyntaxTokenizer > Tokenizer;

	/** True if syntax highlighting is enabled, false to fallback to plain text */
	bool bSyntaxHighlightingEnabled;

	FPLRichTextSyntaxHighlighterTextLayoutMarshaller(TSharedPtr< FPrologSyntaxTokenizer > InTokenizer, const FSyntaxTextStyle& InSyntaxTextStyle);

	/** Styles used to display the text */
	FSyntaxTextStyle SyntaxTextStyle;

	/** String representing tabs */
	FString TabString;
	
};
