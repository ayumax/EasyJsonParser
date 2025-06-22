// Copyright 2025 ayumax. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EasyJsonParserV2Enums.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEasyJsonParserV2, Log, All);

/**
 * Debug log output system
 */
class EASYJSONPARSERV2_API FEasyJsonV2DebugLogger
{
public:
	// Output operation logs
	static void LogOperation(const FString& Operation, const FString& Result, const FString& Message);
	
	// Output detailed information
	static void LogDetail(const FString& DetailMessage, int32 IndentLevel = 1);
	
	// Output error information
	static void LogError(const FString& AccessString, const FString& ErrorType, const FString& Suggestion);
	
	// Output performance information
	static void LogPerformance(const FString& Operation, float ElapsedTime);
	
	// Output success information
	static void LogSuccess(const FString& Operation, const FString& Details = FString());
	
	// Detailed log of access string parsing
	static void LogAccessParsing(const FString& AccessString, const TArray<FString>& ParsedSteps);

	// Check if debug mode is enabled
	static bool IsDebugEnabled();
	
	// Get current log level
	static EEasyJsonParserV2DebugLogLevel GetLogLevel();

private:
	
	// Format log messages
	static FString FormatLogMessage(const FString& Category, const FString& Level, const FString& Message);
	
	// Generate string for indentation
	static FString GetIndentString(int32 IndentLevel);
};

/**
 * Scope class for performance measurement
 */
class EASYJSONPARSERV2_API FEasyJsonV2DebugScope
{
public:
	FEasyJsonV2DebugScope(const FString& OperationName);
	~FEasyJsonV2DebugScope();
	
	// Record time at intermediate points
	void LogCheckpoint(const FString& CheckpointName);

private:
	FString OperationName;
	double StartTime;
	TArray<TPair<FString, double>> Checkpoints;
};

// Macros for debug mode
#define EASYJSON_DEBUG_SCOPE(OperationName) \
	FEasyJsonV2DebugScope DebugScope(OperationName)

#define EASYJSON_DEBUG_LOG(Operation, Result, Message) \
	FEasyJsonV2DebugLogger::LogOperation(Operation, Result, Message)

#define EASYJSON_DEBUG_ERROR(AccessString, ErrorType, Suggestion) \
	FEasyJsonV2DebugLogger::LogError(AccessString, ErrorType, Suggestion)

#define EASYJSON_DEBUG_SUCCESS(Operation, Details) \
	FEasyJsonV2DebugLogger::LogSuccess(Operation, Details)

// Global functions for debug mode control
namespace EasyJsonParserV2Debug
{
	// Enable/disable debug mode
	EASYJSONPARSERV2_API void SetDebugEnabled(bool bEnabled);
	
	// Get current debug mode status
	EASYJSONPARSERV2_API bool IsDebugEnabled();
	
	// Set debug log level
	EASYJSONPARSERV2_API void SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel LogLevel);
	
	// Get current debug log level
	EASYJSONPARSERV2_API EEasyJsonParserV2DebugLogLevel GetDebugLogLevel();
}