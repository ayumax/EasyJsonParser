// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EasyJsonObject.h"
#include "EasyJsonParserEnums.h"
#include "EasyJsonParseManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class EASYJSONPARSER_API UEasyJsonParseManager : public UObject
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
	static UEasyJsonObject* LoadFromFile(const FString& FilePath, bool IsAblolute, EEasyJsonParserErrorCode& Result);

	/**
	 * load Json string
	 * @param JsonString - Json file path
	 * @return Json object
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParser", meta = (ExpandEnumAsExecs = "Result"))
	static UEasyJsonObject* LoadFromString(const FString& JsonString, EEasyJsonParserErrorCode& Result);

};
