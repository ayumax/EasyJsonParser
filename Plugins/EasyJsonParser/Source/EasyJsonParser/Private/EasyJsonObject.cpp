// Copyright 2019 ayumax. All Rights Reserved.
#include "EasyJsonObject.h"
#include "Internationalization/Regex.h"

UEasyJsonObject* UEasyJsonObject::CreateEasyJsonObject(TSharedPtr<FJsonObject> JsonObject)
{
	auto newElement = NewObject<UEasyJsonObject>();
	newElement->InnerObject = JsonObject;

	return newElement;
}


int32 UEasyJsonObject::ReadInt(const FString& AccessString, int32 DefaultValue)
{
	auto foundElement = ReadEasyJsonValue(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetIntValue(DefaultValue);
}


float UEasyJsonObject::ReadFloat(const FString& AccessString, float DefaultValue)
{
	auto foundElement = ReadEasyJsonValue(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetFloatValue(DefaultValue);
}

FString UEasyJsonObject::ReadString(const FString& AccessString, const FString& DefaultValue)
{
	auto foundElement = ReadEasyJsonValue(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetStringValue(DefaultValue);
}

bool UEasyJsonObject::ReadBool(const FString& AccessString, bool DefaultValue)
{
	auto foundElement = ReadEasyJsonValue(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetBoolValue(DefaultValue);
}

UEasyJsonObject* UEasyJsonObject::ReadObject(const FString& AccessString, EEasyJsonParserFound& Result)
{
	auto filterArray = ReadObjects(AccessString, Result);

	return filterArray.Num() > 0 ? filterArray[0] : nullptr;
}

TArray<UEasyJsonObject*> UEasyJsonObject::ReadObjects(const FString& AccessString, EEasyJsonParserFound& Result)
{
	TArray<UEasyJsonObject*> foundElements;

	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);

	Result = EEasyJsonParserFound::NotFound;

	auto parentNode = InnerObject;

	for (auto accesseName : Accessers)
	{
		if (!parentNode) break;

		auto beforeParentNode = parentNode;

		FString propertyName;
		int32 arrayIndex = 0;
		bool isArray = IsAccessAsArray(accesseName, propertyName, arrayIndex);

		TArray<TSharedPtr<FJsonObject>> Objects;
		GetObject(parentNode, propertyName, Objects);

		if (Objects.Num() == 0) break;

		if (accesseName.Equals(Accessers.Last()))
		{
			Result = EEasyJsonParserFound::Found;
			for (auto& jsonObject : Objects)
			{
				foundElements.Emplace(UEasyJsonObject::CreateEasyJsonObject(jsonObject));
			}
		}
		else
		{
			parentNode = Objects[arrayIndex];
		}

		if (parentNode == beforeParentNode)
		{
			break;
		}
	}

	return foundElements;
}

UEasyJsonValue* UEasyJsonObject::ReadEasyJsonValue(const FString& AccessString)
{
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);

	auto parentNode = InnerObject;

	for (auto accesseName : Accessers)
	{
		if (!parentNode) break;

		auto beforeParentNode = parentNode;

		FString propertyName;
		int32 arrayIndex = 0;
		bool isArray = IsAccessAsArray(accesseName, propertyName, arrayIndex);

		if (parentNode->HasField(propertyName))
		{
			if (accesseName.Equals(Accessers.Last()))
			{
				return GetJsonValue(parentNode, propertyName, arrayIndex);
			}
			else
			{
				TArray<TSharedPtr<FJsonObject>> Objects;
				GetObject(parentNode, propertyName, Objects);

				if (Objects.Num() > 0)
				{
					parentNode = Objects[arrayIndex];
				}
			}
		}
		

		if (parentNode == beforeParentNode)
		{
			break;
		}
	}

	return nullptr;
}



bool UEasyJsonObject::IsAccessAsArray(const FString& AccessName, FString& ElementName, int32& ArrayIndex)
{
	const FRegexPattern pattern = FRegexPattern(FString(TEXT("(.*)\\[([0-9]+)\\]$")));
	FRegexMatcher matcher(pattern, AccessName);

	while (matcher.FindNext())
	{
		ElementName = matcher.GetCaptureGroup(1);

		FString numStr = matcher.GetCaptureGroup(2);
		if (numStr.IsNumeric())
		{
			ArrayIndex = (FCString::Atoi(*numStr));
		}

		return true;
	}

	ElementName = AccessName;
	ArrayIndex = 0;

	return false;
}

void UEasyJsonObject::GetObject(const TSharedPtr<FJsonObject> TargetObject, const FString& PropertyName, TArray<TSharedPtr<FJsonObject>>& Objects)
{
	if (!TargetObject->HasField(PropertyName)) return;

	const TArray<TSharedPtr<FJsonValue>>* jsonArrayValue;
	if (TargetObject->TryGetArrayField(PropertyName, jsonArrayValue))
	{
		for (auto& arrayValue : *jsonArrayValue)
		{
			const TSharedPtr<FJsonObject>* objectValueInArray;
			if (arrayValue->TryGetObject(objectValueInArray))
			{
				Objects.Emplace(*objectValueInArray);
			}
			else
			{
				Objects.Emplace(nullptr);
			}
		}
	}
	else
	{
		const TSharedPtr<FJsonObject>* objectValue;
		if (TargetObject->TryGetObjectField(PropertyName, objectValue))
		{
			Objects.Emplace(*objectValue);
		}
	}
}

UEasyJsonValue* UEasyJsonObject::GetJsonValue(const TSharedPtr<FJsonObject> TargetObject, const FString& PropertyName, int32 ArrayIndex)
{
	const TArray<TSharedPtr<FJsonValue>>* jsonArrayValue;
	if (TargetObject->TryGetArrayField(PropertyName, jsonArrayValue))
	{
		return UEasyJsonValue::CreateEasyJsonValue((*jsonArrayValue)[ArrayIndex]);
	}

	return UEasyJsonValue::CreateEasyJsonValue(TargetObject->TryGetField(PropertyName));
}