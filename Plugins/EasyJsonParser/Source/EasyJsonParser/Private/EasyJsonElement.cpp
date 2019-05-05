// Copyright 2019 ayumax. All Rights Reserved.
#include "EasyJsonElement.h"
#include "EasyJsonAttribute.h"
#include "Internationalization/Regex.h"

UEasyJsonElement* UEasyJsonElement::CreateElement(UEasyJsonObject* ParentObject, FString Tag, FString Content, int32 _LineNumber)
{
	auto newElement = NewObject<UEasyJsonElement>(ParentObject == nullptr ? (UObject*)GetTransientPackage() : ParentObject);
	newElement->Parent = ParentObject;
	newElement->Name = Tag;
	newElement->Value = Content.TrimStartAndEnd();
	newElement->LineNumber = _LineNumber;

	return newElement;
}


int32 UEasyJsonElement::ReadInt(const FString& AccessString, int32 DefaultValue)
{
	auto foundElement = ReadEasyJsonObject(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetIntValue(DefaultValue);
}


float UEasyJsonElement::ReadFloat(const FString& AccessString, float DefaultValue)
{
	auto foundElement = ReadEasyJsonObject(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetFloatValue(DefaultValue);
}

FString UEasyJsonElement::ReadString(const FString& AccessString, const FString& DefaultValue)
{
	auto foundElement = ReadEasyJsonObject(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetStringValue(DefaultValue);
}

bool UEasyJsonElement::ReadBool(const FString& AccessString, bool DefaultValue)
{
	auto foundElement = ReadEasyJsonObject(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetBoolValue(DefaultValue);
}

UEasyJsonElement* UEasyJsonElement::ReadElement(const FString& AccessString, EEasyJsonParserFound& Result)
{
	auto filterArray = ReadElements(AccessString, Result);

	return filterArray.Num() > 0 ? filterArray[0] : nullptr;
}

TArray<UEasyJsonElement*> UEasyJsonElement::ReadElements(const FString& AccessString, EEasyJsonParserFound& Result)
{
	TArray<UEasyJsonElement*> foundElements;

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

		auto filterNodes = parentNode->GetElementsByTagName(elementName);

		if (i == (Accessers.Num() - 1))
		{
			if (IsArrayAccess)
			{
				if (filterNodes.Num() > arrayIndex)
				{
					foundElements.Emplace(filterNodes[arrayIndex]);
				}	
			}
			else
			{
				foundElements = filterNodes;
			}
		}
		else
		{
			if (filterNodes.Num() > arrayIndex)
			{
				parentNode = filterNodes[arrayIndex];
			}

			if (!parentNode) return foundElements;
		}
	}

	Result = EEasyJsonParserFound::Found;

	return foundElements;
}

UEasyJsonObject* UEasyJsonElement::ReadEasyJsonObject(const FString& AccessString)
{
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);

	auto parentNode = this;

	for (auto accesseName : Accessers)
	{
		if (!parentNode) return nullptr;
		if (accesseName.IsEmpty()) return nullptr;

		if (accesseName[0] == TEXT('@'))
		{
			EEasyJsonParserFound retFound;
			return parentNode->GetAttribute(accesseName.Mid(1), retFound);
		}
		
		FString elementName;
		int32 arrayIndex = 0;
		IsAccessAsArray(accesseName, elementName, arrayIndex);

		auto filterNodes = parentNode->GetElementsByTagName(elementName);
		if (filterNodes.Num() > arrayIndex)
		{
			parentNode = filterNodes[arrayIndex];
		}
		else
		{
			return nullptr;
		}	
	}

	return parentNode;
}

TArray<UEasyJsonElement*> UEasyJsonElement::GetElementsByTagName(const FString& TagName)
{
	TArray<UEasyJsonElement*> foundElements = Children.FilterByPredicate(
		[TagName](UEasyJsonElement* child)
		{
			return child->Name.Equals(TagName, ESearchCase::IgnoreCase);
		});

	return foundElements;
}

UEasyJsonAttribute* UEasyJsonElement::GetAttribute(const FString& AtrributeName, EEasyJsonParserFound& Result)
{
	if (Attributes.Contains(AtrributeName))
	{
		Result = EEasyJsonParserFound::Found;
		return Attributes[AtrributeName];
	}

	Result = EEasyJsonParserFound::NotFound;
	return nullptr;
}

bool UEasyJsonElement::IsAccessAsArray(const FString& AccessName, FString& ElementName, int32& ArrayIndex)
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
	


bool UEasyJsonElement::IsContainAttributeKeys(const TArray<FString>& Keys, TArray<FString>& FoundAttributeKeys)
{
	TArray<FString> attributeKeys;
	Attributes.GetKeys(attributeKeys);

	for (auto key : Keys)
	{
		bool found = false;
		for (auto attributeKey : attributeKeys)
		{
			if (key.Equals(attributeKey, ESearchCase::IgnoreCase))
			{
				found = true;
				FoundAttributeKeys.Emplace(attributeKey);
			}

		}

		if (!found) return false;
	}

	return true;
}
