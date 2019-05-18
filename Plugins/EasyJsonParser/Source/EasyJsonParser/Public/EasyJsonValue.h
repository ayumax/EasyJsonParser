// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dom/JsonValue.h"
#include "EasyJsonValue.generated.h"


UCLASS(BlueprintType, Blueprintable)
class EASYJSONPARSER_API UEasyJsonValue : public UObject
{
	GENERATED_BODY()
	
public:
	static UEasyJsonValue* CreateEasyJsonValue(TSharedPtr<FJsonValue> JsonValue);

public:
	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|GetValue")
	int32 GetIntValue(int32 DefaultValue = 0);

	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|GetValue")
	float GetFloatValue(float DefaultValue = 0.0f);

	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|GetValue")
	FString GetStringValue(FString DefaultValue = TEXT(""));

	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|GetValue")
	bool GetBoolValue(bool DefaultValue = false);

private:
	TSharedPtr<FJsonValue> InnerObject;

};
