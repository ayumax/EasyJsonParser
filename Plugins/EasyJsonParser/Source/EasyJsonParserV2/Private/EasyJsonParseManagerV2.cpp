// Copyright Epic Games, Inc. All Rights Reserved.

#include "EasyJsonParseManagerV2.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

FEasyJsonObjectV2 UEasyJsonParseManagerV2::LoadFromFile(const FString& FilePath, bool IsAbsolute, bool& bSuccess, FString& ErrorMessage)
{
	bSuccess = false;
	ErrorMessage.Empty();
	
	FString AbsolutePath = GetAbsolutePath(FilePath, IsAbsolute);
	
	// Check if file exists
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*AbsolutePath))
	{
		ErrorMessage = FString::Printf(TEXT("File not found: %s"), *AbsolutePath);
		return FEasyJsonObjectV2();
	}
	
	// Load file content
	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *AbsolutePath))
	{
		ErrorMessage = FString::Printf(TEXT("Failed to read file: %s"), *AbsolutePath);
		return FEasyJsonObjectV2();
	}
	
	// Parse JSON
	return LoadFromString(JsonString, bSuccess, ErrorMessage);
}

FEasyJsonObjectV2 UEasyJsonParseManagerV2::LoadFromString(const FString& JsonString, bool& bSuccess, FString& ErrorMessage)
{
	bSuccess = false;
	ErrorMessage.Empty();
	
	if (JsonString.IsEmpty())
	{
		ErrorMessage = TEXT("Empty JSON string");
		return FEasyJsonObjectV2();
	}
	
	FEasyJsonObjectV2 Result = FEasyJsonObjectV2::CreateFromString(JsonString, bSuccess);
	
	if (!bSuccess)
	{
		ErrorMessage = TEXT("Failed to parse JSON");
	}
	
	return Result;
}

bool UEasyJsonParseManagerV2::SaveToFile(const FEasyJsonObjectV2& JsonObject, const FString& FilePath, bool IsAbsolute, FString& ErrorMessage)
{
	ErrorMessage.Empty();
	
	if (!JsonObject.IsValid())
	{
		ErrorMessage = TEXT("Invalid JSON object");
		return false;
	}
	
	FString AbsolutePath = GetAbsolutePath(FilePath, IsAbsolute);
	
	// Ensure directory exists
	FString Directory = FPaths::GetPath(AbsolutePath);
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*Directory))
	{
		if (!FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*Directory))
		{
			ErrorMessage = FString::Printf(TEXT("Failed to create directory: %s"), *Directory);
			return false;
		}
	}
	
	// Convert to string
	FString JsonString = JsonObject.ToString(true);
	
	// Save to file
	if (!FFileHelper::SaveStringToFile(JsonString, *AbsolutePath))
	{
		ErrorMessage = FString::Printf(TEXT("Failed to save file: %s"), *AbsolutePath);
		return false;
	}
	
	return true;
}

FString UEasyJsonParseManagerV2::SaveToString(const FEasyJsonObjectV2& JsonObject, bool bPrettyPrint)
{
	if (!JsonObject.IsValid())
	{
		return FString();
	}
	
	return JsonObject.ToString(bPrettyPrint);
}

FString UEasyJsonParseManagerV2::GetAbsolutePath(const FString& FilePath, bool IsAbsolute)
{
	if (IsAbsolute)
	{
		return FilePath;
	}
	
	// Convert relative path to absolute path (relative to Content directory)
	return FPaths::Combine(FPaths::ProjectContentDir(), FilePath);
}