// Copyright Epic Games, Inc. All Rights Reserved.

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