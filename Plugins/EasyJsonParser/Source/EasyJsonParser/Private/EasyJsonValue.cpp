// Copyright 2019 ayumax. All Rights Reserved.

#include "EasyJsonValue.h"

UEasyJsonValue* UEasyJsonValue::CreateEasyJsonValue(TSharedPtr<FJsonValue> JsonValue)
{
	auto newElement = NewObject<UEasyJsonValue>();
	newElement->InnerObject = JsonValue;

	return newElement;
}

int32 UEasyJsonValue::GetIntValue(int32 DefaultValue)
{
	if (!InnerObject) return DefaultValue;
	if (InnerObject->IsNull()) return DefaultValue;

	int32 intValue = 0;

	if (InnerObject->TryGetNumber(intValue))
	{
		return intValue;
	}

	return DefaultValue;
}

float UEasyJsonValue::GetFloatValue(float DefaultValue)
{
	if (!InnerObject) return DefaultValue;
	if (InnerObject->IsNull()) return DefaultValue;

	double floatValue = 0;

	if (InnerObject->TryGetNumber(floatValue))
	{
		return (float)floatValue;
	}

	return DefaultValue;
}

FString UEasyJsonValue::GetStringValue(FString DefaultValue)
{
	if (!InnerObject) return DefaultValue;
	if (InnerObject->IsNull()) return DefaultValue;

	FString stringValue;

	if (InnerObject->TryGetString(stringValue))
	{
		return stringValue;
	}

	return DefaultValue;
}

bool UEasyJsonValue::GetBoolValue(bool DefaultValue)
{
	if (!InnerObject) return DefaultValue;
	if (InnerObject->IsNull()) return DefaultValue;

	bool boolValue;

	if (InnerObject->TryGetBool(boolValue))
	{
		return boolValue;
	}

	return DefaultValue;
}
