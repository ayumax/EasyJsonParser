// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedAccessParser.generated.h"

USTRUCT(BlueprintType)
struct EASYJSONPARSERV2_API FAccessStep
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString PropertyName;

	UPROPERTY(BlueprintReadOnly)
	TArray<int32> ArrayIndices;

	UPROPERTY(BlueprintReadOnly)
	bool bIsArrayAccess = false;

	FAccessStep()
		: PropertyName(TEXT(""))
		, bIsArrayAccess(false)
	{
	}

	FAccessStep(const FString& InPropertyName)
		: PropertyName(InPropertyName)
		, bIsArrayAccess(false)
	{
	}

	FAccessStep(const FString& InPropertyName, const TArray<int32>& InArrayIndices)
		: PropertyName(InPropertyName)
		, ArrayIndices(InArrayIndices)
		, bIsArrayAccess(true)
	{
	}
};

/**
 * Advanced access string parser that supports nested array access patterns
 * like "matrix[0][1]", "data[1][2][0]", "users[0].contacts[1].emails[0]"
 */
class EASYJSONPARSERV2_API FAdvancedAccessParser
{
public:
	/**
	 * Parse an access string into a series of access steps
	 * @param AccessString The access string to parse (e.g., "users[0].contacts[1].emails[0]")
	 * @return Array of access steps representing the parsed path
	 */
	static TArray<FAccessStep> ParseAccessString(const FString& AccessString);

	/**
	 * Validate if an access string has correct syntax
	 * @param AccessString The access string to validate
	 * @return True if the syntax is valid
	 */
	static bool IsValidAccessString(const FString& AccessString);

	/**
	 * Sanitize an access string by removing extra spaces and invalid characters
	 * @param AccessString The access string to sanitize
	 * @return Sanitized access string
	 */
	static FString SanitizeAccessString(const FString& AccessString);

	/**
	 * Check if an access string contains array access patterns
	 * @param AccessString The access string to check
	 * @return True if it contains array access patterns
	 */
	static bool ContainsArrayAccess(const FString& AccessString);

	/**
	 * Get the maximum nesting depth of arrays in an access string
	 * @param AccessString The access string to analyze
	 * @return Maximum array nesting depth
	 */
	static int32 GetMaxArrayDepth(const FString& AccessString);

private:
	/**
	 * Parse a single access component (e.g., "matrix[0][1]" or "property")
	 * @param Component The component to parse
	 * @return Parsed access step
	 */
	static FAccessStep ParseAccessComponent(const FString& Component);

	/**
	 * Extract array indices from a component (e.g., "[0][1][2]" -> [0, 1, 2])
	 * @param Component The component containing array indices
	 * @param OutPropertyName The property name without array indices
	 * @param OutIndices The extracted array indices
	 * @return True if array indices were found
	 */
	static bool ExtractArrayIndices(const FString& Component, FString& OutPropertyName, TArray<int32>& OutIndices);

	/**
	 * Validate bracket syntax in a component
	 * @param Component The component to validate
	 * @return True if bracket syntax is valid
	 */
	static bool ValidateBracketSyntax(const FString& Component);
};