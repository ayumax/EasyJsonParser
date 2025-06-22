// Copyright 2025 ayumax. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "EasyJsonParserV2Enums.generated.h"

UENUM(BlueprintType)
enum class EEasyJsonParserV2ErrorCode : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	FileNotFound UMETA(DisplayName = "FileNotFound"),
	InvalidJson UMETA(DisplayName = "InvalidJson"),
	Unknown UMETA(DisplayName = "Unknown"),
};

UENUM(BlueprintType)
enum class EEasyJsonParserV2DebugLogLevel : uint8
{
	None = 0 UMETA(DisplayName = "None"),        // No log output
	Basic = 1 UMETA(DisplayName = "Basic"),      // Basic error information only
	Detailed = 2 UMETA(DisplayName = "Detailed"), // Detailed debug information
	Verbose = 3 UMETA(DisplayName = "Verbose")   // Record all operations in detail
};