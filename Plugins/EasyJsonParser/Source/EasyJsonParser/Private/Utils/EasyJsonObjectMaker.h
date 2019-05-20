// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"

class UEasyJsonObject;

class EasyJsonObjectMaker
{
public:
	EasyJsonObjectMaker();
	virtual ~EasyJsonObjectMaker();

	UEasyJsonObject* Parse(FString jsonString, FString& ErrorMessage);

private:
	void MakeEasyJsonValue(TSharedPtr<FJsonObject> JsonObject, UEasyJsonObject* EasyJsonValue);
};
