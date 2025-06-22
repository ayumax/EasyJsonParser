// Copyright 2025 ayumax. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EasyJsonParserV2Enums.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEasyJsonParserV2, Log, All);

/**
 * デバッグログ出力システム
 */
class EASYJSONPARSERV2_API FEasyJsonV2DebugLogger
{
public:
	// 操作ログの出力
	static void LogOperation(const FString& Operation, const FString& Result, const FString& Message);
	
	// 詳細情報の出力
	static void LogDetail(const FString& DetailMessage, int32 IndentLevel = 1);
	
	// エラー情報の出力
	static void LogError(const FString& AccessString, const FString& ErrorType, const FString& Suggestion);
	
	// パフォーマンス情報の出力
	static void LogPerformance(const FString& Operation, float ElapsedTime);
	
	// 成功情報の出力
	static void LogSuccess(const FString& Operation, const FString& Details = FString());
	
	// アクセス文字列解析の詳細ログ
	static void LogAccessParsing(const FString& AccessString, const TArray<FString>& ParsedSteps);

	// デバッグモード有効チェック
	static bool IsDebugEnabled();
	
	// 現在のログレベル取得
	static EEasyJsonParserV2DebugLogLevel GetLogLevel();

private:
	
	// ログメッセージのフォーマット
	static FString FormatLogMessage(const FString& Category, const FString& Level, const FString& Message);
	
	// インデント用文字列生成
	static FString GetIndentString(int32 IndentLevel);
};

/**
 * パフォーマンス測定用のスコープクラス
 */
class EASYJSONPARSERV2_API FEasyJsonV2DebugScope
{
public:
	FEasyJsonV2DebugScope(const FString& OperationName);
	~FEasyJsonV2DebugScope();
	
	// 中間時点でのタイム記録
	void LogCheckpoint(const FString& CheckpointName);

private:
	FString OperationName;
	double StartTime;
	TArray<TPair<FString, double>> Checkpoints;
};

// デバッグモード用マクロ
#define EASYJSON_DEBUG_SCOPE(OperationName) \
	FEasyJsonV2DebugScope DebugScope(OperationName)

#define EASYJSON_DEBUG_LOG(Operation, Result, Message) \
	FEasyJsonV2DebugLogger::LogOperation(Operation, Result, Message)

#define EASYJSON_DEBUG_ERROR(AccessString, ErrorType, Suggestion) \
	FEasyJsonV2DebugLogger::LogError(AccessString, ErrorType, Suggestion)

#define EASYJSON_DEBUG_SUCCESS(Operation, Details) \
	FEasyJsonV2DebugLogger::LogSuccess(Operation, Details)

// デバッグモード制御用のグローバル関数
namespace EasyJsonParserV2Debug
{
	// デバッグモードの有効/無効切り替え
	EASYJSONPARSERV2_API void SetDebugEnabled(bool bEnabled);
	
	// 現在のデバッグモード状態を取得
	EASYJSONPARSERV2_API bool IsDebugEnabled();
	
	// デバッグログレベル設定
	EASYJSONPARSERV2_API void SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel LogLevel);
	
	// 現在のデバッグログレベルを取得
	EASYJSONPARSERV2_API EEasyJsonParserV2DebugLogLevel GetDebugLogLevel();
}