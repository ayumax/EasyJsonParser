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
	None = 0 UMETA(DisplayName = "None"),        // ログ出力なし
	Basic = 1 UMETA(DisplayName = "Basic"),      // 基本的なエラー情報のみ
	Detailed = 2 UMETA(DisplayName = "Detailed"), // 詳細なデバッグ情報
	Verbose = 3 UMETA(DisplayName = "Verbose")   // 全ての操作を詳細記録
};