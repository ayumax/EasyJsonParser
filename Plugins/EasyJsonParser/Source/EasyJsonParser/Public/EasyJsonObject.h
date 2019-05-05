// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EasyJsonObject.generated.h"


UCLASS(BlueprintType, Blueprintable)
class EASYJsonPARSER_API UEasyJsonObject : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|GetValue")
	int32 GetIntValue(int32 DefaultValue = 0);

	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|GetValue")
	float GetFloatValue(float DefaultValue = 0.0f);

	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|GetValue")
	FString GetStringValue(FString DefaultValue = TEXT(""));

	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|GetValue")
	bool GetBoolValue(bool DefaultValue = false);

public:
	UPROPERTY(BlueprintReadOnly, Category = "EasyJsonParser|Object")
	FString Name = TEXT("");

	UPROPERTY(BlueprintReadOnly, Category = "EasyJsonParser|Object")
	FString Value = TEXT("");
	
	UPROPERTY(BlueprintReadOnly, Category = "EasyJsonParser|Object")
	UEasyJsonObject* Parent = nullptr;

};
