// Copyright 2025 ayumax. All Rights Reserved.

#include "EasyJsonParserV2Debug.h"
#include "Engine/Engine.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/DateTime.h"

DEFINE_LOG_CATEGORY(LogEasyJsonParserV2);

static EEasyJsonParserV2DebugLogLevel GDebugLogLevel = EEasyJsonParserV2DebugLogLevel::None;
static bool GDebugModeEnabled = false;

void FEasyJsonV2DebugLogger::LogOperation(const FString& Operation, const FString& Result, const FString& Message)
{
    if (!IsDebugEnabled() || GetLogLevel() == EEasyJsonParserV2DebugLogLevel::None)
    {
        return;
    }

    FString FormattedMessage = FormatLogMessage(TEXT("Operation"), TEXT("Info"), 
        FString::Printf(TEXT("[%s] Result: %s | %s"), *Operation, *Result, *Message));
    
    UE_LOG(LogEasyJsonParserV2, Warning, TEXT("%s"), *FormattedMessage);
}

void FEasyJsonV2DebugLogger::LogDetail(const FString& DetailMessage, int32 IndentLevel)
{
    if (!IsDebugEnabled() || GetLogLevel() < EEasyJsonParserV2DebugLogLevel::Detailed)
    {
        return;
    }

    FString IndentString = GetIndentString(IndentLevel);
    FString FormattedMessage = FormatLogMessage(TEXT("Detail"), TEXT("Info"), 
        FString::Printf(TEXT("%s%s"), *IndentString, *DetailMessage));
    
    UE_LOG(LogEasyJsonParserV2, Warning, TEXT("%s"), *FormattedMessage);
}

void FEasyJsonV2DebugLogger::LogError(const FString& AccessString, const FString& ErrorType, const FString& Suggestion)
{
    if (!IsDebugEnabled() || GetLogLevel() == EEasyJsonParserV2DebugLogLevel::None)
    {
        return;
    }

    FString FormattedMessage = FormatLogMessage(TEXT("Error"), TEXT("Error"), 
        FString::Printf(TEXT("Path: '%s' | Type: %s | Suggestion: %s"), *AccessString, *ErrorType, *Suggestion));
    
    UE_LOG(LogEasyJsonParserV2, Error, TEXT("%s"), *FormattedMessage);
}

void FEasyJsonV2DebugLogger::LogPerformance(const FString& Operation, float ElapsedTime)
{
    if (!IsDebugEnabled() || GetLogLevel() < EEasyJsonParserV2DebugLogLevel::Detailed)
    {
        return;
    }

    FString FormattedMessage = FormatLogMessage(TEXT("Performance"), TEXT("Info"), 
        FString::Printf(TEXT("[%s] Elapsed: %.3fms"), *Operation, ElapsedTime * 1000.0f));
    
    UE_LOG(LogEasyJsonParserV2, Warning, TEXT("%s"), *FormattedMessage);
}

void FEasyJsonV2DebugLogger::LogSuccess(const FString& Operation, const FString& Details)
{
    if (!IsDebugEnabled() || GetLogLevel() < EEasyJsonParserV2DebugLogLevel::Basic)
    {
        return;
    }

    FString DetailPart = Details.IsEmpty() ? TEXT("") : FString::Printf(TEXT(" | %s"), *Details);
    FString FormattedMessage = FormatLogMessage(TEXT("Success"), TEXT("Info"), 
        FString::Printf(TEXT("[%s]%s"), *Operation, *DetailPart));
    
    UE_LOG(LogEasyJsonParserV2, Warning, TEXT("%s"), *FormattedMessage);
}

void FEasyJsonV2DebugLogger::LogAccessParsing(const FString& AccessString, const TArray<FString>& ParsedSteps)
{
    if (!IsDebugEnabled() || GetLogLevel() < EEasyJsonParserV2DebugLogLevel::Verbose)
    {
        return;
    }

    FString StepsString = FString::Join(ParsedSteps, TEXT(" -> "));
    FString FormattedMessage = FormatLogMessage(TEXT("AccessParse"), TEXT("Info"), 
        FString::Printf(TEXT("'%s' parsed as: %s"), *AccessString, *StepsString));
    
    UE_LOG(LogEasyJsonParserV2, Warning, TEXT("%s"), *FormattedMessage);
}

bool FEasyJsonV2DebugLogger::IsDebugEnabled()
{
    return GDebugModeEnabled;
}

EEasyJsonParserV2DebugLogLevel FEasyJsonV2DebugLogger::GetLogLevel()
{
    return GDebugLogLevel;
}

FString FEasyJsonV2DebugLogger::FormatLogMessage(const FString& Category, const FString& Level, const FString& Message)
{
    FDateTime Now = FDateTime::Now();
    return FString::Printf(TEXT("[%s][EasyJsonV2][%s][%s] %s"), 
        *Now.ToString(TEXT("%H:%M:%S.%f")), *Category, *Level, *Message);
}

FString FEasyJsonV2DebugLogger::GetIndentString(int32 IndentLevel)
{
    FString IndentString;
    for (int32 i = 0; i < IndentLevel; ++i)
    {
        IndentString += TEXT("  ");
    }
    return IndentString;
}

// FEasyJsonV2DebugScope implementation
FEasyJsonV2DebugScope::FEasyJsonV2DebugScope(const FString& OperationName)
    : OperationName(OperationName)
    , StartTime(FPlatformTime::Seconds())
{
    if (FEasyJsonV2DebugLogger::IsDebugEnabled() && 
        FEasyJsonV2DebugLogger::GetLogLevel() >= EEasyJsonParserV2DebugLogLevel::Detailed)
    {
        FEasyJsonV2DebugLogger::LogDetail(FString::Printf(TEXT("Starting operation: %s"), *OperationName), 0);
    }
}

FEasyJsonV2DebugScope::~FEasyJsonV2DebugScope()
{
    if (FEasyJsonV2DebugLogger::IsDebugEnabled() && 
        FEasyJsonV2DebugLogger::GetLogLevel() >= EEasyJsonParserV2DebugLogLevel::Detailed)
    {
        double EndTime = FPlatformTime::Seconds();
        float ElapsedTime = static_cast<float>(EndTime - StartTime);
        
        FEasyJsonV2DebugLogger::LogPerformance(OperationName, ElapsedTime);
        
        // Output detailed checkpoint logs
        if (FEasyJsonV2DebugLogger::GetLogLevel() >= EEasyJsonParserV2DebugLogLevel::Verbose && Checkpoints.Num() > 0)
        {
            FEasyJsonV2DebugLogger::LogDetail(FString::Printf(TEXT("Checkpoints for %s:"), *OperationName), 1);
            for (const auto& Checkpoint : Checkpoints)
            {
                float CheckpointTime = static_cast<float>(Checkpoint.Value - StartTime);
                FEasyJsonV2DebugLogger::LogDetail(
                    FString::Printf(TEXT("- %s: %.3fms"), *Checkpoint.Key, CheckpointTime * 1000.0f), 2);
            }
        }
    }
}

void FEasyJsonV2DebugScope::LogCheckpoint(const FString& CheckpointName)
{
    if (FEasyJsonV2DebugLogger::IsDebugEnabled() && 
        FEasyJsonV2DebugLogger::GetLogLevel() >= EEasyJsonParserV2DebugLogLevel::Verbose)
    {
        double CheckpointTime = FPlatformTime::Seconds();
        Checkpoints.Add(TPair<FString, double>(CheckpointName, CheckpointTime));
        
        float ElapsedFromStart = static_cast<float>(CheckpointTime - StartTime);
        FEasyJsonV2DebugLogger::LogDetail(
            FString::Printf(TEXT("Checkpoint '%s' in %s: %.3fms"), 
                *CheckpointName, *OperationName, ElapsedFromStart * 1000.0f), 1);
    }
}

// Global functions for debug mode control (planned to be moved to Blueprint function library in the future)
namespace EasyJsonParserV2Debug
{
    void SetDebugEnabled(bool bEnabled)
    {
        GDebugModeEnabled = bEnabled;
        if (bEnabled)
        {
            UE_LOG(LogEasyJsonParserV2, Warning, TEXT("EasyJsonParserV2 Debug Mode ENABLED"));
        }
        else
        {
            UE_LOG(LogEasyJsonParserV2, Warning, TEXT("EasyJsonParserV2 Debug Mode DISABLED"));
        }
    }
    
    bool IsDebugEnabled()
    {
        return GDebugModeEnabled;
    }
    
    void SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel DebugLogLevel)
    {
        GDebugLogLevel = DebugLogLevel;
        UE_LOG(LogEasyJsonParserV2, Warning, TEXT("EasyJsonParserV2 Debug Log Level set to: %d"), static_cast<int32>(DebugLogLevel));
    }
    
    EEasyJsonParserV2DebugLogLevel GetDebugLogLevel()
    {
        return GDebugLogLevel;
    }
}