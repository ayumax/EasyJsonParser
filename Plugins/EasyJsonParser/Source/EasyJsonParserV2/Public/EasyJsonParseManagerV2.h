// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EasyJsonObjectV2.h"
#include "EasyJsonParserV2Enums.h"
#include "EasyJsonParseManagerV2.generated.h"

UCLASS(BlueprintType, Blueprintable)
class EASYJSONPARSERV2_API UEasyJsonParseManagerV2 : public UObject
{
	GENERATED_BODY()

public:
	// File loading (returns struct)
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2")
	static FEasyJsonObjectV2 LoadFromFile(const FString& FilePath, bool IsAbsolute, bool& bSuccess, FString& ErrorMessage);

	// String loading (returns struct)
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2")
	static FEasyJsonObjectV2 LoadFromString(const FString& JsonString, bool& bSuccess, FString& ErrorMessage);

	// File saving
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2")
	static bool SaveToFile(const FEasyJsonObjectV2& JsonObject, const FString& FilePath, bool IsAbsolute, FString& ErrorMessage);

	// String conversion
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2")
	static FString SaveToString(const FEasyJsonObjectV2& JsonObject, bool bPrettyPrint = false);

private:
	// Helper method to get absolute path
	static FString GetAbsolutePath(const FString& FilePath, bool IsAbsolute);
};