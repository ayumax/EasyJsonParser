// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EasyJsonElement.h"
#include "EasyJsonParserEnums.h"
#include "EasyJsonParseManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class EASYJsonPARSER_API UEasyJsonParseManager : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * load Json file
	 * @param FilePath - Json file path
	 * @param IsAblolute - true:FilePath is absolute path, false:Relative path from "Content"
	 * @return Json object
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParser", meta = (ExpandEnumAsExecs = "Result"))
	static UEasyJsonElement* LoadFromFile(const FString& FilePath, bool IsAblolute, EEasyJsonParserErrorCode& Result, FString& ErrorMessage);

	/**
	 * load Json string
	 * @param JsonString - Json file path
	 * @return Json object
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParser", meta = (ExpandEnumAsExecs = "Result"))
	static UEasyJsonElement* LoadFromString(const FString& JsonString, EEasyJsonParserErrorCode& Result, FString& ErrorMessage);

};
