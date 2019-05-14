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

UEasyJsonObject* UEasyJsonObject::ReadElement(const FString& AccessString, EEasyJsonParserFound& Result)
{
	auto filterArray = ReadElements(AccessString, Result);

	return filterArray.Num() > 0 ? filterArray[0] : nullptr;
}

TArray<UEasyJsonObject*> UEasyJsonObject::ReadElements(const FString& AccessString, EEasyJsonParserFound& Result)
{
	TArray<UEasyJsonObject*> foundElements;

	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);

	Result = EEasyJsonParserFound::NotFound;

	auto parentNode = this;

	for (int i = 0; i < Accessers.Num(); ++i)
	{
		auto accesseName = Accessers[i];

		if (accesseName.IsEmpty()) return foundElements;

		FString elementName;
		int32 arrayIndex = 0;
		bool IsArrayAccess = IsAccessAsArray(accesseName, elementName, arrayIndex);

		a
	}

	Result = EEasyJsonParserFound::Found;

	return foundElements;
}

UEasyJsonValue* UEasyJsonObject::ReadEasyJsonValue(const FString& AccessString)
{
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);

	auto parentNode = InnerObject;

	for (auto accesseName : Accessers)
	{
		if (!parentNode) return nullptr;
		if (accesseName.IsEmpty()) return nullptr;

		
		FString propertyName;
		int32 arrayIndex = 0;
		bool isArray = IsAccessAsArray(accesseName, propertyName, arrayIndex);

		if (parentNode->HasField(propertyName))
		{
			if (isArray)
			{
				const TArray<TSharedPtr<FJsonValue>>* arrayValue;
				if (parentNode->TryGetArrayField(propertyName, arrayValue))
				{
					if (arrayValue->Num() > arrayIndex)
					{
						auto value = (*arrayValue)[arrayIndex];
						parentNode = value->AsObject();

						if (accesseName.Equals(Accessers.Last()))
						{
							return UEasyJsonValue::CreateEasyJsonValue(value);
						}
					}
				}
			}
			else
			{
				const TSharedPtr<FJsonObject>* objectValue;
				if (parentNode->TryGetObjectField(propertyName, objectValue))
				{
					parentNode = *objectValue;
				}
				else
				{
					if (accesseName.Equals(Accessers.Last()))
					{
						return UEasyJsonValue::CreateEasyJsonValue(parentNode->TryGetField(propertyName));
					}
				}
			}
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
	