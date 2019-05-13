// Copyright 2019 ayumax. All Rights Reserved.
#include "EasyJsonObject.h"
#include "Internationalization/Regex.h"

UEasyJsonObject* UEasyJsonObject::CreateElement(UEasyJsonValue* ParentObject, FString Tag, FString Content, int32 _LineNumber)
{
	auto newElement = NewObject<UEasyJsonObject>(ParentObject == nullptr ? (UObject*)GetTransientPackage() : ParentObject);
	newElement->LineNumber = _LineNumber;

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

		if (accesseName[0] == TEXT('@'))
		{
			return foundElements;
		}

		FString elementName;
		int32 arrayIndex = 0;
		bool IsArrayAccess = IsAccessAsArray(accesseName, elementName, arrayIndex);


	}

	Result = EEasyJsonParserFound::Found;

	return foundElements;
}

UEasyJsonValue* UEasyJsonObject::ReadEasyJsonValue(const FString& AccessString)
{
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);

	auto parentNode = this;

	for (auto accesseName : Accessers)
	{
		if (!parentNode) return nullptr;
		if (accesseName.IsEmpty()) return nullptr;

		
		FString elementName;
		int32 arrayIndex = 0;
		IsAccessAsArray(accesseName, elementName, arrayIndex);

		
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
	