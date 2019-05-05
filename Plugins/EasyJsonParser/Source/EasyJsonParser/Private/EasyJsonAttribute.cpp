// Copyright 2019 ayumax. All Rights Reserved.
#include "EasyJsonAttribute.h"
#include "EasyJsonElement.h"

UEasyJsonAttribute* UEasyJsonAttribute::CreateAttribute(UEasyJsonElement* ParentObject, FString _Name, FString _Value)
{
	auto newAttribute = NewObject<UEasyJsonAttribute>(ParentObject == nullptr ? (UObject*)GetTransientPackage() : ParentObject);
	newAttribute->Parent = ParentObject;
	newAttribute->Name = _Name;
	newAttribute->Value = _Value.TrimStartAndEnd();

	return newAttribute;
}