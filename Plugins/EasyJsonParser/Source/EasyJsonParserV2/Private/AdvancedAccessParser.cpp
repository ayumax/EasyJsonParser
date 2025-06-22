// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdvancedAccessParser.h"
#include "EasyJsonParserV2Debug.h"
#include "Internationalization/Regex.h"

TArray<FAccessStep> FAdvancedAccessParser::ParseAccessString(const FString& AccessString)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("ParseAccessString(%s)"), *AccessString));
	
	TArray<FAccessStep> Steps;
	
	if (AccessString.IsEmpty())
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("EmptyAccessString"), TEXT("Access string cannot be empty"));
		return Steps;
	}
	
	// Sanitize the access string first
	FString SanitizedString = SanitizeAccessString(AccessString);
	
	// Split by dots to get components
	TArray<FString> Components;
	SanitizedString.ParseIntoArray(Components, TEXT("."), true);
	
	// Parse each component
	for (const FString& Component : Components)
	{
		if (!Component.IsEmpty())
		{
			FAccessStep Step = ParseAccessComponent(Component);
			if (!Step.PropertyName.IsEmpty())
			{
				Steps.Add(Step);
			}
		}
	}
	
	EASYJSON_DEBUG_SUCCESS(TEXT("ParseAccessString"), FString::Printf(TEXT("Parsed %d steps"), Steps.Num()));
	return Steps;
}

bool FAdvancedAccessParser::IsValidAccessString(const FString& AccessString)
{
	if (AccessString.IsEmpty())
	{
		return false;
	}
	
	// Check basic syntax rules
	if (AccessString.StartsWith(TEXT(".")) || AccessString.EndsWith(TEXT(".")))
	{
		return false;
	}
	
	// Check for consecutive dots
	if (AccessString.Contains(TEXT("..")))
	{
		return false;
	}
	
	// Split by dots and validate each component
	TArray<FString> Components;
	AccessString.ParseIntoArray(Components, TEXT("."), true);
	
	for (const FString& Component : Components)
	{
		if (!ValidateBracketSyntax(Component))
		{
			return false;
		}
	}
	
	return true;
}

FString FAdvancedAccessParser::SanitizeAccessString(const FString& AccessString)
{
	FString Result = AccessString;
	
	// Remove leading/trailing whitespace
	Result = Result.TrimStartAndEnd();
	
	// Remove spaces around dots
	Result = Result.Replace(TEXT(" . "), TEXT("."));
	Result = Result.Replace(TEXT(" ."), TEXT("."));
	Result = Result.Replace(TEXT(". "), TEXT("."));
	
	// Remove spaces around brackets
	Result = Result.Replace(TEXT(" ["), TEXT("["));
	Result = Result.Replace(TEXT("[ "), TEXT("["));
	Result = Result.Replace(TEXT(" ]"), TEXT("]"));
	Result = Result.Replace(TEXT("] "), TEXT("]"));
	
	return Result;
}

bool FAdvancedAccessParser::ContainsArrayAccess(const FString& AccessString)
{
	return AccessString.Contains(TEXT("[")) && AccessString.Contains(TEXT("]"));
}

int32 FAdvancedAccessParser::GetMaxArrayDepth(const FString& AccessString)
{
	int32 MaxDepth = 0;
	
	TArray<FAccessStep> Steps = ParseAccessString(AccessString);
	for (const FAccessStep& Step : Steps)
	{
		if (Step.bIsArrayAccess)
		{
			MaxDepth = FMath::Max(MaxDepth, Step.ArrayIndices.Num());
		}
	}
	
	return MaxDepth;
}

FAccessStep FAdvancedAccessParser::ParseAccessComponent(const FString& Component)
{
	FString PropertyName;
	TArray<int32> ArrayIndices;
	
	if (ExtractArrayIndices(Component, PropertyName, ArrayIndices))
	{
		return FAccessStep(PropertyName, ArrayIndices);
	}
	else
	{
		return FAccessStep(Component);
	}
}

bool FAdvancedAccessParser::ExtractArrayIndices(const FString& Component, FString& OutPropertyName, TArray<int32>& OutIndices)
{
	OutIndices.Empty();
	
	// Find the first bracket
	int32 FirstBracketIndex = Component.Find(TEXT("["));
	if (FirstBracketIndex == INDEX_NONE)
	{
		OutPropertyName = Component;
		return false;
	}
	
	// Extract property name (everything before the first bracket)
	OutPropertyName = Component.Left(FirstBracketIndex);
	
	// Extract all bracket pairs using regex
	FString BracketPart = Component.Mid(FirstBracketIndex);
	
	// Regex pattern to match [number] patterns
	const FRegexPattern Pattern = FRegexPattern(TEXT("\\[(\\d+)\\]"));
	FRegexMatcher Matcher(Pattern, BracketPart);
	
	// Find all matches
	while (Matcher.FindNext())
	{
		FString IndexStr = Matcher.GetCaptureGroup(1);
		if (IndexStr.IsNumeric())
		{
			int32 Index = FCString::Atoi(*IndexStr);
			OutIndices.Add(Index);
		}
	}
	
	return OutIndices.Num() > 0;
}

bool FAdvancedAccessParser::ValidateBracketSyntax(const FString& Component)
{
	if (Component.IsEmpty())
	{
		return false;
	}
	
	// Count brackets
	int32 OpenBrackets = 0;
	int32 CloseBrackets = 0;
	
	for (int32 i = 0; i < Component.Len(); i++)
	{
		TCHAR Char = Component[i];
		if (Char == TEXT('['))
		{
			OpenBrackets++;
		}
		else if (Char == TEXT(']'))
		{
			CloseBrackets++;
			
			// Check if we have more close brackets than open brackets at any point
			if (CloseBrackets > OpenBrackets)
			{
				return false;
			}
		}
	}
	
	// Must have equal number of open and close brackets
	if (OpenBrackets != CloseBrackets)
	{
		return false;
	}
	
	// If there are brackets, validate the pattern
	if (OpenBrackets > 0)
	{
		// Use regex to validate that all brackets contain valid indices
		const FRegexPattern Pattern = FRegexPattern(TEXT("^([a-zA-Z_][a-zA-Z0-9_]*)(\\[\\d+\\])*$"));
		FRegexMatcher Matcher(Pattern, Component);
		
		return Matcher.FindNext();
	}
	
	// No brackets, just validate property name
	const FRegexPattern PropertyPattern = FRegexPattern(TEXT("^[a-zA-Z_][a-zA-Z0-9_]*$"));
	FRegexMatcher PropertyMatcher(PropertyPattern, Component);
	
	return PropertyMatcher.FindNext();
}