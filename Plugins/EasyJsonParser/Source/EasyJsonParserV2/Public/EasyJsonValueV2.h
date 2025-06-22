// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonValue.h"
#include "EasyJsonValueV2.generated.h"

USTRUCT(BlueprintType)
struct EASYJSONPARSERV2_API FEasyJsonValueV2
{
	GENERATED_BODY()

public:
	// Constructors
	FEasyJsonValueV2();
	FEasyJsonValueV2(TSharedPtr<FJsonValue> InJsonValue);
	
	// Copy constructor and assignment
	FEasyJsonValueV2(const FEasyJsonValueV2& Other);
	FEasyJsonValueV2& operator=(const FEasyJsonValueV2& Other);
	
	// Move constructor and assignment
	FEasyJsonValueV2(FEasyJsonValueV2&& Other) noexcept;
	FEasyJsonValueV2& operator=(FEasyJsonValueV2&& Other) noexcept;
	
	// Value getters
	int32 GetIntValue(int32 DefaultValue = 0) const;
	float GetFloatValue(float DefaultValue = 0.0f) const;
	FString GetStringValue(const FString& DefaultValue = TEXT("")) const;
	bool GetBoolValue(bool DefaultValue = false) const;
	
	// Type checkers
	bool IsNull() const;
	bool IsNumber() const;
	bool IsString() const;
	bool IsBool() const;
	bool IsArray() const;
	bool IsObject() const;
	
	// Validity check
	FORCEINLINE bool IsValid() const { return InnerValue.IsValid(); }
	
	// Get underlying JSON value
	TSharedPtr<FJsonValue> GetJsonValue() const { return InnerValue; }

private:
	TSharedPtr<FJsonValue> InnerValue;
};