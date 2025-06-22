// Copyright Epic Games, Inc. All Rights Reserved.

#include "EasyJsonObjectV2.h"
#include "Internationalization/Regex.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

FEasyJsonObjectV2::FEasyJsonObjectV2()
{
}

FEasyJsonObjectV2::FEasyJsonObjectV2(TSharedPtr<FJsonObject> InJsonObject)
	: InnerObject(InJsonObject)
{
}

FEasyJsonObjectV2::FEasyJsonObjectV2(const FEasyJsonObjectV2& Other)
	: InnerObject(Other.InnerObject)
{
}

FEasyJsonObjectV2& FEasyJsonObjectV2::operator=(const FEasyJsonObjectV2& Other)
{
	if (this != &Other)
	{
		InnerObject = Other.InnerObject;
	}
	return *this;
}

FEasyJsonObjectV2::FEasyJsonObjectV2(FEasyJsonObjectV2&& Other) noexcept
	: InnerObject(MoveTemp(Other.InnerObject))
{
}

FEasyJsonObjectV2& FEasyJsonObjectV2::operator=(FEasyJsonObjectV2&& Other) noexcept
{
	if (this != &Other)
	{
		InnerObject = MoveTemp(Other.InnerObject);
	}
	return *this;
}

int32 FEasyJsonObjectV2::ReadInt(const FString& AccessString, int32 DefaultValue) const
{
	FEasyJsonValueV2 FoundElement = ReadEasyJsonValue(AccessString);
	if (!FoundElement.IsValid()) return DefaultValue;
	
	return FoundElement.GetIntValue(DefaultValue);
}

float FEasyJsonObjectV2::ReadFloat(const FString& AccessString, float DefaultValue) const
{
	FEasyJsonValueV2 FoundElement = ReadEasyJsonValue(AccessString);
	if (!FoundElement.IsValid()) return DefaultValue;
	
	return FoundElement.GetFloatValue(DefaultValue);
}

FString FEasyJsonObjectV2::ReadString(const FString& AccessString, const FString& DefaultValue) const
{
	FEasyJsonValueV2 FoundElement = ReadEasyJsonValue(AccessString);
	if (!FoundElement.IsValid()) return DefaultValue;
	
	return FoundElement.GetStringValue(DefaultValue);
}

bool FEasyJsonObjectV2::ReadBool(const FString& AccessString, bool DefaultValue) const
{
	FEasyJsonValueV2 FoundElement = ReadEasyJsonValue(AccessString);
	if (!FoundElement.IsValid()) return DefaultValue;
	
	return FoundElement.GetBoolValue(DefaultValue);
}

FEasyJsonObjectV2 FEasyJsonObjectV2::ReadObject(const FString& AccessString, bool& bFound) const
{
	TArray<FEasyJsonObjectV2> FilterArray = ReadObjects(AccessString, bFound);
	
	if (FilterArray.Num() > 0)
	{
		return FilterArray[0];
	}
	
	bFound = false;
	return FEasyJsonObjectV2();
}

TArray<FEasyJsonObjectV2> FEasyJsonObjectV2::ReadObjects(const FString& AccessString, bool& bFound) const
{
	TArray<FEasyJsonObjectV2> FoundElements;
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	bFound = false;
	
	if (!IsValid())
	{
		return FoundElements;
	}
	
	TSharedPtr<FJsonObject> ParentNode = InnerObject;
	
	for (const FString& AccessName : Accessers)
	{
		if (!ParentNode) break;
		
		TSharedPtr<FJsonObject> BeforeParentNode = ParentNode;
		
		FString PropertyName;
		int32 ArrayIndex = 0;
		bool bIsArray = IsAccessAsArray(AccessName, PropertyName, ArrayIndex);
		
		TArray<TSharedPtr<FJsonObject>> Objects;
		GetObject(ParentNode, PropertyName, Objects);
		
		if (Objects.Num() == 0) break;
		
		if (AccessName.Equals(Accessers.Last()))
		{
			bFound = true;
			for (const TSharedPtr<FJsonObject>& JsonObject : Objects)
			{
				FoundElements.Add(FEasyJsonObjectV2(JsonObject));
			}
		}
		else
		{
			if (ArrayIndex < Objects.Num())
			{
				ParentNode = Objects[ArrayIndex];
			}
			else
			{
				break;
			}
		}
		
		if (ParentNode == BeforeParentNode)
		{
			break;
		}
	}
	
	return FoundElements;
}

void FEasyJsonObjectV2::WriteInt(const FString& AccessString, int32 Value)
{
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueNumber(static_cast<double>(Value)));
	CreateValue(AccessString, NewValue);
}

void FEasyJsonObjectV2::WriteFloat(const FString& AccessString, float Value)
{
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueNumber(static_cast<double>(Value)));
	CreateValue(AccessString, NewValue);
}

void FEasyJsonObjectV2::WriteString(const FString& AccessString, const FString& Value)
{
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueString(Value));
	CreateValue(AccessString, NewValue);
}

void FEasyJsonObjectV2::WriteBool(const FString& AccessString, bool Value)
{
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueBoolean(Value));
	CreateValue(AccessString, NewValue);
}

void FEasyJsonObjectV2::WriteObject(const FString& AccessString, const FEasyJsonObjectV2& Object)
{
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	if (Object.IsValid())
	{
		TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueObject(Object.InnerObject));
		CreateValue(AccessString, NewValue);
	}
}

void FEasyJsonObjectV2::AddIntToArray(const FString& AccessString, int32 Value)
{
	// TODO: Implement in write phase
}

void FEasyJsonObjectV2::AddFloatToArray(const FString& AccessString, float Value)
{
	// TODO: Implement in write phase
}

void FEasyJsonObjectV2::AddStringToArray(const FString& AccessString, const FString& Value)
{
	// TODO: Implement in write phase
}

void FEasyJsonObjectV2::AddBoolToArray(const FString& AccessString, bool Value)
{
	// TODO: Implement in write phase
}

void FEasyJsonObjectV2::AddObjectToArray(const FString& AccessString, const FEasyJsonObjectV2& Object)
{
	// TODO: Implement in write phase
}

FEasyJsonObjectV2 FEasyJsonObjectV2::CreateEmpty()
{
	return FEasyJsonObjectV2(MakeShareable(new FJsonObject()));
}

FEasyJsonObjectV2 FEasyJsonObjectV2::CreateFromString(const FString& JsonString, bool& bSuccess)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	
	bSuccess = FJsonSerializer::Deserialize(Reader, JsonObject);
	
	if (bSuccess && JsonObject.IsValid())
	{
		return FEasyJsonObjectV2(JsonObject);
	}
	
	return FEasyJsonObjectV2();
}

FEasyJsonObjectV2 FEasyJsonObjectV2::CreateFromJsonObject(TSharedPtr<FJsonObject> JsonObject)
{
	return FEasyJsonObjectV2(JsonObject);
}

FString FEasyJsonObjectV2::ToString(bool bPrettyPrint) const
{
	if (!IsValid())
	{
		return FString();
	}
	
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = bPrettyPrint 
		? TJsonWriterFactory<>::Create(&OutputString)
		: TJsonWriterFactory<>::Create(&OutputString, 0);
	
	FJsonSerializer::Serialize(InnerObject.ToSharedRef(), Writer);
	
	return OutputString;
}

TSharedPtr<FJsonObject> FEasyJsonObjectV2::ToJsonObject() const
{
	return InnerObject;
}

bool FEasyJsonObjectV2::operator==(const FEasyJsonObjectV2& Other) const
{
	// Simple pointer comparison
	return InnerObject == Other.InnerObject;
}

bool FEasyJsonObjectV2::operator!=(const FEasyJsonObjectV2& Other) const
{
	return !(*this == Other);
}

FEasyJsonValueV2 FEasyJsonObjectV2::ReadEasyJsonValue(const FString& AccessString) const
{
	if (!IsValid())
	{
		return FEasyJsonValueV2();
	}
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	TSharedPtr<FJsonObject> ParentNode = InnerObject;
	
	for (const FString& AccessName : Accessers)
	{
		if (!ParentNode) break;
		
		TSharedPtr<FJsonObject> BeforeParentNode = ParentNode;
		
		FString PropertyName;
		int32 ArrayIndex = 0;
		bool bIsArray = IsAccessAsArray(AccessName, PropertyName, ArrayIndex);
		
		if (ParentNode->HasField(PropertyName))
		{
			if (AccessName.Equals(Accessers.Last()))
			{
				// Get the value
				TSharedPtr<FJsonValue> Value = ParentNode->TryGetField(PropertyName);
				
				if (Value.IsValid() && Value->Type == EJson::Array)
				{
					const TArray<TSharedPtr<FJsonValue>>* ArrayValue;
					if (Value->TryGetArray(ArrayValue) && ArrayIndex < ArrayValue->Num())
					{
						return FEasyJsonValueV2((*ArrayValue)[ArrayIndex]);
					}
				}
				else
				{
					return FEasyJsonValueV2(Value);
				}
			}
			else
			{
				TArray<TSharedPtr<FJsonObject>> Objects;
				GetObject(ParentNode, PropertyName, Objects);
				
				if (Objects.Num() > 0 && ArrayIndex < Objects.Num())
				{
					ParentNode = Objects[ArrayIndex];
				}
			}
		}
		
		if (ParentNode == BeforeParentNode)
		{
			break;
		}
	}
	
	return FEasyJsonValueV2();
}

bool FEasyJsonObjectV2::IsAccessAsArray(const FString& AccessName, FString& ElementName, int32& ArrayIndex) const
{
	const FRegexPattern Pattern = FRegexPattern(FString(TEXT("(.*)\\[([0-9]+)\\]$")));
	FRegexMatcher Matcher(Pattern, AccessName);
	
	if (Matcher.FindNext())
	{
		ElementName = Matcher.GetCaptureGroup(1);
		
		FString NumStr = Matcher.GetCaptureGroup(2);
		if (NumStr.IsNumeric())
		{
			ArrayIndex = FCString::Atoi(*NumStr);
		}
		
		return true;
	}
	
	ElementName = AccessName;
	ArrayIndex = 0;
	
	return false;
}

void FEasyJsonObjectV2::GetObject(const TSharedPtr<FJsonObject> TargetObject, const FString& PropertyName, TArray<TSharedPtr<FJsonObject>>& Objects) const
{
	if (!TargetObject->HasField(PropertyName)) return;
	
	const TArray<TSharedPtr<FJsonValue>>* JsonArrayValue;
	if (TargetObject->TryGetArrayField(PropertyName, JsonArrayValue))
	{
		for (const TSharedPtr<FJsonValue>& ArrayValue : *JsonArrayValue)
		{
			const TSharedPtr<FJsonObject>* ObjectValueInArray;
			if (ArrayValue->TryGetObject(ObjectValueInArray))
			{
				Objects.Add(*ObjectValueInArray);
			}
			else
			{
				Objects.Add(nullptr);
			}
		}
	}
	else
	{
		const TSharedPtr<FJsonObject>* ObjectValue;
		if (TargetObject->TryGetObjectField(PropertyName, ObjectValue))
		{
			Objects.Add(*ObjectValue);
		}
	}
}

TSharedPtr<FJsonObject> FEasyJsonObjectV2::CreateOrGetObject(const FString& AccessString)
{
	// TODO: Implement in write phase
	return nullptr;
}

TSharedPtr<FJsonValue> FEasyJsonObjectV2::CreateValue(const FString& AccessString, TSharedPtr<FJsonValue> NewValue)
{
	// TODO: Implement in write phase
	return nullptr;
}