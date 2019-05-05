// Copyright 2019 ayumax. All Rights Reserved.

#include "EasyJsonParseManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "EasyJsonElement.h"
#include "Utils/CustomJsonParser.h"


UEasyJsonElement* UEasyJsonParseManager::LoadFromString(const FString& JsonString, EEasyJsonParserErrorCode& Result, FString& ErrorMessage)
{
	CustomJsonParser parser;
	FString _errorMessage;

	auto rootElement = parser.Parse(JsonString, _errorMessage);
	Result = rootElement != nullptr ? EEasyJsonParserErrorCode::Successed : EEasyJsonParserErrorCode::Failed;
	ErrorMessage = _errorMessage;

	return rootElement;
}

UEasyJsonElement* UEasyJsonParseManager::LoadFromFile(const FString& FilePath, bool IsAblolute, EEasyJsonParserErrorCode& Result, FString& ErrorMessage)
{
	auto readPath = FilePath;
	if (!IsAblolute)
	{
		readPath = FPaths::Combine(FPaths::ProjectContentDir(), FilePath);
	}

	if (!FPaths::FileExists(readPath)) return nullptr;

	FString JsonString;

	FFileHelper::LoadFileToString(JsonString, *readPath);

	return LoadFromString(JsonString, Result, ErrorMessage);
}
