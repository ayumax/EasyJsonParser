// Copyright 2025 ayumax. All Rights Reserved.

#include "EasyJsonValueV2.h"

FEasyJsonValueV2::FEasyJsonValueV2()
{
}

FEasyJsonValueV2::FEasyJsonValueV2(TSharedPtr<FJsonValue> InJsonValue)
	: InnerValue(InJsonValue)
{
}

FEasyJsonValueV2::FEasyJsonValueV2(const FEasyJsonValueV2& Other)
	: InnerValue(Other.InnerValue)
{
}

FEasyJsonValueV2& FEasyJsonValueV2::operator=(const FEasyJsonValueV2& Other)
{
	if (this != &Other)
	{
		InnerValue = Other.InnerValue;
	}
	return *this;
}

FEasyJsonValueV2::FEasyJsonValueV2(FEasyJsonValueV2&& Other) noexcept
	: InnerValue(MoveTemp(Other.InnerValue))
{
}

FEasyJsonValueV2& FEasyJsonValueV2::operator=(FEasyJsonValueV2&& Other) noexcept
{
	if (this != &Other)
	{
		InnerValue = MoveTemp(Other.InnerValue);
	}
	return *this;
}

int32 FEasyJsonValueV2::GetIntValue(int32 DefaultValue) const
{
	if (!IsValid())
	{
		return DefaultValue;
	}
	
	double DoubleValue;
	if (InnerValue->TryGetNumber(DoubleValue))
	{
		return static_cast<int32>(DoubleValue);
	}
	
	return DefaultValue;
}

float FEasyJsonValueV2::GetFloatValue(float DefaultValue) const
{
	if (!IsValid())
	{
		return DefaultValue;
	}
	
	double DoubleValue;
	if (InnerValue->TryGetNumber(DoubleValue))
	{
		return static_cast<float>(DoubleValue);
	}
	
	return DefaultValue;
}

FString FEasyJsonValueV2::GetStringValue(const FString& DefaultValue) const
{
	if (!IsValid())
	{
		return DefaultValue;
	}
	
	FString StringValue;
	if (InnerValue->TryGetString(StringValue))
	{
		return StringValue;
	}
	
	return DefaultValue;
}

bool FEasyJsonValueV2::GetBoolValue(bool DefaultValue) const
{
	if (!IsValid())
	{
		return DefaultValue;
	}
	
	bool BoolValue;
	if (InnerValue->TryGetBool(BoolValue))
	{
		return BoolValue;
	}
	
	return DefaultValue;
}

bool FEasyJsonValueV2::IsNull() const
{
	return IsValid() && InnerValue->IsNull();
}

bool FEasyJsonValueV2::IsNumber() const
{
	return IsValid() && InnerValue->Type == EJson::Number;
}

bool FEasyJsonValueV2::IsString() const
{
	return IsValid() && InnerValue->Type == EJson::String;
}

bool FEasyJsonValueV2::IsBool() const
{
	return IsValid() && InnerValue->Type == EJson::Boolean;
}

bool FEasyJsonValueV2::IsArray() const
{
	return IsValid() && InnerValue->Type == EJson::Array;
}

bool FEasyJsonValueV2::IsObject() const
{
	return IsValid() && InnerValue->Type == EJson::Object;
}