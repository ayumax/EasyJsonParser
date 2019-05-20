// Copyright 2019 ayumax. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"

#include "EasyJsonValue.h"
#include "EasyJsonParserEnums.h"
#include "Dom/JsonObject.h"
#include "EasyJsonObject.generated.h"

class UEasyJsonAttribute;

UCLASS(BlueprintType, Blueprintable)
class EASYJSONPARSER_API UEasyJsonObject : public UObject
{
	GENERATED_BODY()
	
public:
	static UEasyJsonObject* CreateEasyJsonObject(TSharedPtr<FJsonObject> JsonObject);

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
	UEasyJsonObject* ReadObject(const FString& AccessString, EEasyJsonParserFound& Result);

	UFUNCTION(BlueprintCallable, Category = "EasyJsonParser|ReadValue", meta = (ExpandEnumAsExecs = "Result"))
	TArray<UEasyJsonObject*> ReadObjects(const FString& AccessString, EEasyJsonParserFound& Result);



public:
	UEasyJsonValue* ReadEasyJsonValue(const FString& AccessString);

private:
	bool IsAccessAsArray(const FString& AccessName, FString& ElementName, int32& ArrayIndex);
	void GetObject(const TSharedPtr<FJsonObject> TargetObject, const FString& PropertyName, TArray<TSharedPtr<FJsonObject>>& Objects);
	UEasyJsonValue* GetJsonValue(const TSharedPtr<FJsonObject> TargetObject, const FString& PropertyName, int32 ArrayIndex);

private:
	TSharedPtr<FJsonObject> InnerObject;

};
