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
	jsonString = jsonString.TrimStartAndEnd();

	if (jsonString[0] == TEXT('['))
	{
		jsonString = FString::Printf(TEXT("{\"root\":%s}"), *jsonString);
	}

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(jsonString);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{	
		return UEasyJsonObject::CreateEasyJsonObject(JsonObject);
	}

	return nullptr;
}
