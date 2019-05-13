// Copyright 2019 ayumax. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"

#include "EasyJsonValue.h"
#include "EasyJsonParserEnums.h"
#include "EasyJsonObject.generated.h"

class UEasyJsonAttribute;

UCLASS(BlueprintType, Blueprintable)
class EASYJSONPARSER_API UEasyJsonObject : public UObject
{
	GENERATED_BODY()
	
public:
	static UEasyJsonObject* CreateElement(UEasyJsonValue* ParentObject, FString Tag, FString Content, int32 LineNumber);

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
	UEasyJsonObject* ReadElement(const FString& AccessString, EEasyJsonParserFound& Result);

	UFUNCTION(BlueprintCallable, Category = "EasyJsonParser|ReadValue", meta = (ExpandEnumAsExecs = "Result"))
	TArray<UEasyJsonObject*> ReadElements(const FString& AccessString, EEasyJsonParserFound& Result);



public:
	UEasyJsonValue* ReadEasyJsonValue(const FString& AccessString);

private:
	bool IsAccessAsArray(const FString& AccessName, FString& ElementName, int32& ArrayIndex);


public:
	UPROPERTY(BlueprintReadOnly, Category = "EasyJsonParser|Object")
	TMap<FString, UEasyJsonObject*> Objects;

	UPROPERTY(BlueprintReadOnly, Category = "EasyJsonParser|Object")
	TMap<FString, UEasyJsonValue*> Values;

};
