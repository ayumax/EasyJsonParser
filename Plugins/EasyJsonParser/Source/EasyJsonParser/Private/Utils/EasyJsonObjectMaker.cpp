// Copyright 2019 ayumax. All Rights Reserved.
#include "EasyJsonObjectMaker.h"
#include "EasyJsonValue.h"
#include "EasyJsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

EasyJsonObjectMaker::EasyJsonObjectMaker()
{
}

EasyJsonObjectMaker::~EasyJsonObjectMaker()
{
}

UEasyJsonObject* EasyJsonObjectMaker::Parse(FString jsonString, FString &ErrorMessage)
{
	
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(jsonString);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		UEasyJsonObject* retObject = NewObject<UEasyJsonObject>();
		
		MakeEasyJsonValue(JsonObject, retObject);
		
		return retObject;
	}

	return nullptr;
}

void EasyJsonObjectMaker::MakeEasyJsonValue(TSharedPtr<FJsonObject> JsonObject, UEasyJsonObject* EasyJsonValue)
{
	for (auto& jsonValuePair : JsonObject->Values)
	{
		if (jsonValuePair.Value->AsObject())
		{

		}
	}
}