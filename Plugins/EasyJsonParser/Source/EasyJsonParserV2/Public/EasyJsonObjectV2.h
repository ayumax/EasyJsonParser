// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "EasyJsonValueV2.h"
#include "EasyJsonObjectV2.generated.h"

USTRUCT(BlueprintType)
struct EASYJSONPARSERV2_API FEasyJsonObjectV2
{
	GENERATED_BODY()

public:
	// Constructors
	FEasyJsonObjectV2();
	FEasyJsonObjectV2(TSharedPtr<FJsonObject> InJsonObject);
	
	// Copy constructor and assignment
	FEasyJsonObjectV2(const FEasyJsonObjectV2& Other);
	FEasyJsonObjectV2& operator=(const FEasyJsonObjectV2& Other);
	
	// Move constructor and assignment
	FEasyJsonObjectV2(FEasyJsonObjectV2&& Other) noexcept;
	FEasyJsonObjectV2& operator=(FEasyJsonObjectV2&& Other) noexcept;

	// Read methods
	int32 ReadInt(const FString& AccessString, int32 DefaultValue = 0) const;
	float ReadFloat(const FString& AccessString, float DefaultValue = 0.0f) const;
	FString ReadString(const FString& AccessString, const FString& DefaultValue = TEXT("")) const;
	bool ReadBool(const FString& AccessString, bool DefaultValue = false) const;
	
	// Object read methods (return structs)
	FEasyJsonObjectV2 ReadObject(const FString& AccessString, bool& bFound) const;
	TArray<FEasyJsonObjectV2> ReadObjects(const FString& AccessString, bool& bFound) const;

	// Write methods
	void WriteInt(const FString& AccessString, int32 Value);
	void WriteFloat(const FString& AccessString, float Value);
	void WriteString(const FString& AccessString, const FString& Value);
	void WriteBool(const FString& AccessString, bool Value);
	void WriteObject(const FString& AccessString, const FEasyJsonObjectV2& Object);

	// Array manipulation
	void AddIntToArray(const FString& AccessString, int32 Value);
	void AddFloatToArray(const FString& AccessString, float Value);
	void AddStringToArray(const FString& AccessString, const FString& Value);
	void AddBoolToArray(const FString& AccessString, bool Value);
	void AddObjectToArray(const FString& AccessString, const FEasyJsonObjectV2& Object);

	// Static creation methods
	static FEasyJsonObjectV2 CreateEmpty();
	static FEasyJsonObjectV2 CreateFromString(const FString& JsonString, bool& bSuccess);
	static FEasyJsonObjectV2 CreateFromJsonObject(TSharedPtr<FJsonObject> JsonObject);

	// Conversion methods
	FString ToString(bool bPrettyPrint = false) const;
	TSharedPtr<FJsonObject> ToJsonObject() const;
	
	// Validity check
	FORCEINLINE bool IsValid() const { return InnerObject.IsValid(); }
	
	// Comparison operators
	bool operator==(const FEasyJsonObjectV2& Other) const;
	bool operator!=(const FEasyJsonObjectV2& Other) const;

private:
	// Internal JSON object
	TSharedPtr<FJsonObject> InnerObject;
	
	// Helper methods
	FEasyJsonValueV2 ReadEasyJsonValue(const FString& AccessString) const;
	bool IsAccessAsArray(const FString& AccessName, FString& ElementName, int32& ArrayIndex) const;
	void GetObject(const TSharedPtr<FJsonObject> TargetObject, const FString& PropertyName, TArray<TSharedPtr<FJsonObject>>& Objects) const;
	TSharedPtr<FJsonObject> CreateOrGetObject(const FString& AccessString);
	TSharedPtr<FJsonValue> CreateValue(const FString& AccessString, TSharedPtr<FJsonValue> NewValue);
};