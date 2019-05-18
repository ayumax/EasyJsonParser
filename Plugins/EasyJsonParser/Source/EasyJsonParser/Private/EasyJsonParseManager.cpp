// Copyright 2019 ayumax. All Rights Reserved.

#include "EasyJsonParseManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "EasyJsonObject.h"
#include "Utils/EasyJsonObjectMaker.h"


UEasyJsonObject* UEasyJsonParseManager::LoadFromString(const FString& JsonString, EEasyJsonParserErrorCode& Result)
{
	EasyJsonObjectMaker objectMaker;
	FString _errorMessage;

	auto rootElement = objectMaker.Parse(JsonString, _errorMessage);
	Result = rootElement != nullptr ? EEasyJsonParserErrorCode::Successed : EEasyJsonParserErrorCode::Failed;

	return rootElement;
}

UEasyJsonObject* UEasyJsonParseManager::LoadFromFile(const FString& FilePath, bool IsAblolute, EEasyJsonParserErrorCode& Result)
{
	auto readPath = FilePath;
	if (!IsAblolute)
	{
		readPath = FPaths::Combine(FPaths::ProjectContentDir(), FilePath);
	}

	if (!FPaths::FileExists(readPath)) return nullptr;

	FString JsonString;

	FFileHelper::LoadFileToString(JsonString, *readPath);

	return LoadFromString(JsonString, Result);
}
