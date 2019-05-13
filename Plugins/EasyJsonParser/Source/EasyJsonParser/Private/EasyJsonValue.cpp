// Copyright 2019 ayumax. All Rights Reserved.

#include "EasyJsonValue.h"

int32 UEasyJsonValue::GetIntValue(int32 DefaultValue)
{
	if (Value.IsEmpty()) return DefaultValue;

	int32 _index = 0;

	if (Value.IsNumeric() && !Value.FindChar(TEXT('.'), _index))
	{
		return FCString::Atoi(*Value);
	}
		
	return DefaultValue;
}

float UEasyJsonValue::GetFloatValue(float DefaultValue)
{
	if (Value.IsEmpty()) return DefaultValue;

	auto isSuccess = Value.IsNumeric();
	return isSuccess ? FCString::Atof(*Value) : DefaultValue;
}

FString UEasyJsonValue::GetStringValue(FString DefaultValue)
{
	if (Value.IsEmpty()) return DefaultValue;

	return Value;
}

bool UEasyJsonValue::GetBoolValue(bool DefaultValue)
{
	if (Value.IsEmpty()) return DefaultValue;

	if (Value.Equals(TEXT("true"), ESearchCase::IgnoreCase))
	{
		return true;
	}
	else if (Value.Equals(TEXT("false"), ESearchCase::IgnoreCase))
	{
		return false;
	}

	return DefaultValue;
}
