// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "EasyJsonObject.h"
#include "EasyJsonParserEnums.h"
#include "EasyJsonElement.generated.h"

class UEasyJsonAttribute;

UCLASS(BlueprintType, Blueprintable)
class EASYJsonPARSER_API UEasyJsonElement : public UEasyJsonObject
{
	GENERATED_BODY()
	
public:
	static UEasyJsonElement* CreateElement(UEasyJsonObject* ParentObject, FString Tag, FString Content, int32 LineNumber);

public:
	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|ReadValue")
	int32 ReadInt(const FString& AccessString, int32 DefaultValue = 0);

	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|ReadValue")
	float ReadFloat(const FString& AccessString, float DefaultValue = 0.0f);

	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|ReadValue")
	FString ReadString(const FString& AccessString, const FString& DefaultValue = TEXT(""));

	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|ReadValue")
	bool ReadBool(const FString& AccessString, bool DefaultValue = false);

	UFUNCTION(BlueprintCallable, Category = "EasyJsonParser|ReadValue", meta = (ExpandEnumAsExecs = "Result"))
	UEasyJsonElement* ReadElement(const FString& AccessString, EEasyJsonParserFound& Result);

	UFUNCTION(BlueprintCallable, Category = "EasyJsonParser|ReadValue", meta = (ExpandEnumAsExecs = "Result"))
	TArray<UEasyJsonElement*> ReadElements(const FString& AccessString, EEasyJsonParserFound& Result);

	UFUNCTION(BlueprintPure, Category = "EasyJsonParser|Object", meta = (ExpandEnumAsExecs = "Result"))
	UEasyJsonAttribute* GetAttribute(const FString& AtrributeName, EEasyJsonParserFound& Result);


public:
	UEasyJsonObject* ReadEasyJsonObject(const FString& AccessString);
	TArray<UEasyJsonElement*> GetElementsByTagName(const FString& TagName);
	bool IsContainAttributeKeys(const TArray<FString>& Keys, TArray<FString>& FoundAttributeKeys);

private:
	bool IsAccessAsArray(const FString& AccessName, FString& ElementName, int32& ArrayIndex);


public:
	UPROPERTY(BlueprintReadOnly, Category = "EasyJsonParser|Object")
	int32 LineNumber = 0;

	UPROPERTY(BlueprintReadOnly, Category = "EasyJsonParser|Object")
	TArray<UEasyJsonElement*> Children;

	UPROPERTY(BlueprintReadOnly, Category = "EasyJsonParser|Object")
	TMap<FString, UEasyJsonAttribute*> Attributes;

	UPROPERTY(BlueprintReadOnly, Category = "EasyJsonParser|Object")
	TArray<FString> Comments;
};
