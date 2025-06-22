// Copyright 2025 ayumax. All Rights Reserved.

#include "EasyJsonParserV2BlueprintLibrary.h"
#include "EasyJsonParseManagerV2.h"
#include "EasyJsonParserV2Debug.h"

// ========================================
// JSON読み込み機能
// ========================================

FEasyJsonObjectV2 UEasyJsonParserV2BlueprintLibrary::LoadJsonFromFile(const FString& FilePath, bool bAbsolutePath, bool& bSuccess, FString& ErrorMessage)
{
	return UEasyJsonParseManagerV2::LoadFromFile(FilePath, bAbsolutePath, bSuccess, ErrorMessage);
}

FEasyJsonObjectV2 UEasyJsonParserV2BlueprintLibrary::LoadJsonFromString(const FString& JsonString, bool& bSuccess, FString& ErrorMessage)
{
	return UEasyJsonParseManagerV2::LoadFromString(JsonString, bSuccess, ErrorMessage);
}

FEasyJsonObjectV2 UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject()
{
	return FEasyJsonObjectV2::CreateEmpty();
}

// ========================================
// JSON読み込み操作
// ========================================

int32 UEasyJsonParserV2BlueprintLibrary::ReadInt(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, int32 DefaultValue)
{
	return JsonObject.ReadInt(AccessString, DefaultValue);
}

float UEasyJsonParserV2BlueprintLibrary::ReadFloat(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, float DefaultValue)
{
	return JsonObject.ReadFloat(AccessString, DefaultValue);
}

FString UEasyJsonParserV2BlueprintLibrary::ReadString(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FString& DefaultValue)
{
	return JsonObject.ReadString(AccessString, DefaultValue);
}

bool UEasyJsonParserV2BlueprintLibrary::ReadBool(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, bool DefaultValue)
{
	return JsonObject.ReadBool(AccessString, DefaultValue);
}

FEasyJsonObjectV2 UEasyJsonParserV2BlueprintLibrary::ReadObject(const FEasyJsonObjectV2& JsonObject, const FString& AccessString)
{
	bool bFound = false;
	return JsonObject.ReadObject(AccessString, bFound);
}

TArray<FEasyJsonObjectV2> UEasyJsonParserV2BlueprintLibrary::ReadObjects(const FEasyJsonObjectV2& JsonObject, const FString& AccessString)
{
	bool bFound = false;
	return JsonObject.ReadObjects(AccessString, bFound);
}

// ========================================
// JSON書き込み操作
// ========================================

void UEasyJsonParserV2BlueprintLibrary::WriteInt(FEasyJsonObjectV2& JsonObject, const FString& AccessString, int32 Value)
{
	JsonObject.WriteInt(AccessString, Value);
}

void UEasyJsonParserV2BlueprintLibrary::WriteFloat(FEasyJsonObjectV2& JsonObject, const FString& AccessString, float Value)
{
	JsonObject.WriteFloat(AccessString, Value);
}

void UEasyJsonParserV2BlueprintLibrary::WriteString(FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FString& Value)
{
	JsonObject.WriteString(AccessString, Value);
}

void UEasyJsonParserV2BlueprintLibrary::WriteBool(FEasyJsonObjectV2& JsonObject, const FString& AccessString, bool Value)
{
	JsonObject.WriteBool(AccessString, Value);
}

void UEasyJsonParserV2BlueprintLibrary::WriteObject(FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FEasyJsonObjectV2& Value)
{
	JsonObject.WriteObject(AccessString, Value);
}

// ========================================
// 配列操作
// ========================================

void UEasyJsonParserV2BlueprintLibrary::AddIntToArray(FEasyJsonObjectV2& JsonObject, const FString& AccessString, int32 Value)
{
	JsonObject.AddIntToArray(AccessString, Value);
}

void UEasyJsonParserV2BlueprintLibrary::AddFloatToArray(FEasyJsonObjectV2& JsonObject, const FString& AccessString, float Value)
{
	JsonObject.AddFloatToArray(AccessString, Value);
}

void UEasyJsonParserV2BlueprintLibrary::AddStringToArray(FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FString& Value)
{
	JsonObject.AddStringToArray(AccessString, Value);
}

void UEasyJsonParserV2BlueprintLibrary::AddBoolToArray(FEasyJsonObjectV2& JsonObject, const FString& AccessString, bool Value)
{
	JsonObject.AddBoolToArray(AccessString, Value);
}

void UEasyJsonParserV2BlueprintLibrary::AddObjectToArray(FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FEasyJsonObjectV2& Value)
{
	JsonObject.AddObjectToArray(AccessString, Value);
}

// ========================================
// JSON保存機能
// ========================================

void UEasyJsonParserV2BlueprintLibrary::SaveJsonToFile(const FEasyJsonObjectV2& JsonObject, const FString& FilePath, bool bAbsolutePath, bool bPrettyPrint, bool& bSuccess, FString& ErrorMessage)
{
	bSuccess = UEasyJsonParseManagerV2::SaveToFile(JsonObject, FilePath, bAbsolutePath, ErrorMessage);
}

FString UEasyJsonParserV2BlueprintLibrary::JsonToString(const FEasyJsonObjectV2& JsonObject, bool bPrettyPrint)
{
	return JsonObject.ToString(bPrettyPrint);
}

// ========================================
// ユーティリティ機能
// ========================================

bool UEasyJsonParserV2BlueprintLibrary::IsJsonObjectValid(const FEasyJsonObjectV2& JsonObject)
{
	return JsonObject.IsValid();
}

bool UEasyJsonParserV2BlueprintLibrary::AreJsonObjectsEqual(const FEasyJsonObjectV2& JsonObjectA, const FEasyJsonObjectV2& JsonObjectB)
{
	// Check if both objects are valid
	if (!JsonObjectA.IsValid() && !JsonObjectB.IsValid())
	{
		return true; // Both null/invalid, consider equal
	}
	
	if (!JsonObjectA.IsValid() || !JsonObjectB.IsValid())
	{
		return false; // One is null, one is not
	}
	
	// Convert both to JSON strings in a normalized format for comparison
	// Use compact format (no pretty print) to avoid formatting differences
	FString JsonStringA = JsonToString(JsonObjectA, false);
	FString JsonStringB = JsonToString(JsonObjectB, false);
	
	return JsonStringA == JsonStringB;
}

// ========================================
// デバッグ機能
// ========================================

void UEasyJsonParserV2BlueprintLibrary::SetDebugMode(bool bEnable)
{
	::EasyJsonParserV2Debug::SetDebugEnabled(bEnable);
}

bool UEasyJsonParserV2BlueprintLibrary::IsDebugMode()
{
	return ::EasyJsonParserV2Debug::IsDebugEnabled();
}

void UEasyJsonParserV2BlueprintLibrary::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel InLogLevel)
{
	::EasyJsonParserV2Debug::SetDebugLogLevel(InLogLevel);
}

EEasyJsonParserV2DebugLogLevel UEasyJsonParserV2BlueprintLibrary::GetDebugLogLevel()
{
	return ::EasyJsonParserV2Debug::GetDebugLogLevel();
}