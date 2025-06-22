// Copyright Epic Games, Inc. All Rights Reserved.

#include "EasyJsonObjectV2.h"
#include "EasyJsonParserV2Debug.h"
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
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("ReadInt(%s)"), *AccessString));
	
	FEasyJsonValueV2 FoundElement = ReadEasyJsonValue(AccessString);
	if (!FoundElement.IsValid()) 
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("PathNotFound"), TEXT("Check if the path exists and contains an integer value"));
		return DefaultValue;
	}
	
	int32 Result = FoundElement.GetIntValue(DefaultValue);
	EASYJSON_DEBUG_SUCCESS(TEXT("ReadInt"), FString::Printf(TEXT("Value: %d"), Result));
	return Result;
}

float FEasyJsonObjectV2::ReadFloat(const FString& AccessString, float DefaultValue) const
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("ReadFloat(%s)"), *AccessString));
	
	FEasyJsonValueV2 FoundElement = ReadEasyJsonValue(AccessString);
	if (!FoundElement.IsValid()) 
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("PathNotFound"), TEXT("Check if the path exists and contains a float value"));
		return DefaultValue;
	}
	
	float Result = FoundElement.GetFloatValue(DefaultValue);
	EASYJSON_DEBUG_SUCCESS(TEXT("ReadFloat"), FString::Printf(TEXT("Value: %f"), Result));
	return Result;
}

FString FEasyJsonObjectV2::ReadString(const FString& AccessString, const FString& DefaultValue) const
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("ReadString(%s)"), *AccessString));
	
	FEasyJsonValueV2 FoundElement = ReadEasyJsonValue(AccessString);
	if (!FoundElement.IsValid()) 
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("PathNotFound"), TEXT("Check if the path exists and contains a string value"));
		return DefaultValue;
	}
	
	FString Result = FoundElement.GetStringValue(DefaultValue);
	EASYJSON_DEBUG_SUCCESS(TEXT("ReadString"), FString::Printf(TEXT("Value: '%s'"), *Result));
	return Result;
}

bool FEasyJsonObjectV2::ReadBool(const FString& AccessString, bool DefaultValue) const
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("ReadBool(%s)"), *AccessString));
	
	FEasyJsonValueV2 FoundElement = ReadEasyJsonValue(AccessString);
	if (!FoundElement.IsValid()) 
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("PathNotFound"), TEXT("Check if the path exists and contains a boolean value"));
		return DefaultValue;
	}
	
	bool Result = FoundElement.GetBoolValue(DefaultValue);
	EASYJSON_DEBUG_SUCCESS(TEXT("ReadBool"), FString::Printf(TEXT("Value: %s"), Result ? TEXT("true") : TEXT("false")));
	return Result;
}

FEasyJsonObjectV2 FEasyJsonObjectV2::ReadObject(const FString& AccessString, bool& bFound) const
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("ReadObject(%s)"), *AccessString));
	
	TArray<FEasyJsonObjectV2> FilterArray = ReadObjects(AccessString, bFound);
	
	if (FilterArray.Num() > 0)
	{
		EASYJSON_DEBUG_SUCCESS(TEXT("ReadObject"), TEXT("Object found"));
		return FilterArray[0];
	}
	
	EASYJSON_DEBUG_ERROR(AccessString, TEXT("ObjectNotFound"), TEXT("Check if the path exists and contains an object"));
	bFound = false;
	return FEasyJsonObjectV2();
}

TArray<FEasyJsonObjectV2> FEasyJsonObjectV2::ReadObjects(const FString& AccessString, bool& bFound) const
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("ReadObjects(%s)"), *AccessString));
	
	TArray<FEasyJsonObjectV2> FoundElements;
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	bFound = false;
	
	if (!IsValid())
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("InvalidObject"), TEXT("JSON object is not valid"));
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
	
	if (FoundElements.Num() > 0)
	{
		bFound = true;
		EASYJSON_DEBUG_SUCCESS(TEXT("ReadObjects"), FString::Printf(TEXT("Found %d objects"), FoundElements.Num()));
	}
	else
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("ArrayNotFound"), TEXT("Check if the path exists and contains an array"));
	}
	
	return FoundElements;
}

void FEasyJsonObjectV2::WriteInt(const FString& AccessString, int32 Value)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("WriteInt(%s, %d)"), *AccessString, Value));
	
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueNumber(static_cast<double>(Value)));
	CreateValue(AccessString, NewValue);
	
	EASYJSON_DEBUG_SUCCESS(TEXT("WriteInt"), FString::Printf(TEXT("Written value %d to path '%s'"), Value, *AccessString));
}

void FEasyJsonObjectV2::WriteFloat(const FString& AccessString, float Value)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("WriteFloat(%s, %f)"), *AccessString, Value));
	
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueNumber(static_cast<double>(Value)));
	CreateValue(AccessString, NewValue);
	
	EASYJSON_DEBUG_SUCCESS(TEXT("WriteFloat"), FString::Printf(TEXT("Written value %f to path '%s'"), Value, *AccessString));
}

void FEasyJsonObjectV2::WriteString(const FString& AccessString, const FString& Value)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("WriteString(%s, '%s')"), *AccessString, *Value));
	
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueString(Value));
	CreateValue(AccessString, NewValue);
	
	EASYJSON_DEBUG_SUCCESS(TEXT("WriteString"), FString::Printf(TEXT("Written value '%s' to path '%s'"), *Value, *AccessString));
}

void FEasyJsonObjectV2::WriteBool(const FString& AccessString, bool Value)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("WriteBool(%s, %s)"), *AccessString, Value ? TEXT("true") : TEXT("false")));
	
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueBoolean(Value));
	CreateValue(AccessString, NewValue);
	
	EASYJSON_DEBUG_SUCCESS(TEXT("WriteBool"), FString::Printf(TEXT("Written value %s to path '%s'"), Value ? TEXT("true") : TEXT("false"), *AccessString));
}

void FEasyJsonObjectV2::WriteObject(const FString& AccessString, const FEasyJsonObjectV2& Object)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("WriteObject(%s)"), *AccessString));
	
	if (Object.IsValid())
	{
		TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueObject(Object.InnerObject));
		CreateValue(AccessString, NewValue);
		EASYJSON_DEBUG_SUCCESS(TEXT("WriteObject"), FString::Printf(TEXT("Written object to path '%s'"), *AccessString));
	}
	else
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("InvalidObject"), TEXT("The object to write is not valid"));
	}
}

void FEasyJsonObjectV2::AddIntToArray(const FString& AccessString, int32 Value)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("AddIntToArray(%s, %d)"), *AccessString, Value));
	
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	if (Accessers.Num() == 0)
	{
		return;
	}
	
	const FString& FinalAccessor = Accessers.Last();
	// For AddIntToArray, the final accessor should be the array property name
	// (no array index notation expected)
	FString ArrayPropertyName = FinalAccessor;
	
	// Get the parent object - for "numbers" this should be the root object
	// for "user.numbers" this should be the "user" object
	TSharedPtr<FJsonObject> ParentObject;
	if (Accessers.Num() == 1)
	{
		// Direct property on root object
		ParentObject = InnerObject;
	}
	else
	{
		// Nested property - get parent path
		TArray<FString> ParentAccessers = Accessers;
		ParentAccessers.RemoveAt(ParentAccessers.Num() - 1);
		FString ParentPath = FString::Join(ParentAccessers, TEXT("."));
		ParentObject = CreateOrGetObject(ParentPath);
	}
	
	if (!ParentObject.IsValid())
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("PathCreationFailed"), TEXT("Could not create or get parent object"));
		return;
	}
	
	// Get existing array or create new one
	const TArray<TSharedPtr<FJsonValue>>* ExistingArray;
	TArray<TSharedPtr<FJsonValue>> ModifiedArray;
	
	if (ParentObject->TryGetArrayField(ArrayPropertyName, ExistingArray))
	{
		ModifiedArray = *ExistingArray;
	}
	
	// Add the new value
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueNumber(static_cast<double>(Value)));
	ModifiedArray.Add(NewValue);
	
	ParentObject->SetArrayField(ArrayPropertyName, ModifiedArray);
	
	EASYJSON_DEBUG_SUCCESS(TEXT("AddIntToArray"), FString::Printf(TEXT("Added value %d to array '%s'"), Value, *AccessString));
}

void FEasyJsonObjectV2::AddFloatToArray(const FString& AccessString, float Value)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("AddFloatToArray(%s, %f)"), *AccessString, Value));
	
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	if (Accessers.Num() == 0)
	{
		return;
	}
	
	const FString& FinalAccessor = Accessers.Last();
	// For AddFloatToArray, the final accessor should be the array property name
	// (no array index notation expected)
	FString ArrayPropertyName = FinalAccessor;
	
	// Get the parent object - for "numbers" this should be the root object
	// for "user.numbers" this should be the "user" object
	TSharedPtr<FJsonObject> ParentObject;
	if (Accessers.Num() == 1)
	{
		// Direct property on root object
		ParentObject = InnerObject;
	}
	else
	{
		// Nested property - get parent path
		TArray<FString> ParentAccessers = Accessers;
		ParentAccessers.RemoveAt(ParentAccessers.Num() - 1);
		FString ParentPath = FString::Join(ParentAccessers, TEXT("."));
		ParentObject = CreateOrGetObject(ParentPath);
	}
	
	if (!ParentObject.IsValid())
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("PathCreationFailed"), TEXT("Could not create or get parent object"));
		return;
	}
	
	// Get existing array or create new one
	const TArray<TSharedPtr<FJsonValue>>* ExistingArray;
	TArray<TSharedPtr<FJsonValue>> ModifiedArray;
	
	if (ParentObject->TryGetArrayField(ArrayPropertyName, ExistingArray))
	{
		ModifiedArray = *ExistingArray;
	}
	
	// Add the new value
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueNumber(static_cast<double>(Value)));
	ModifiedArray.Add(NewValue);
	
	ParentObject->SetArrayField(ArrayPropertyName, ModifiedArray);
	
	EASYJSON_DEBUG_SUCCESS(TEXT("AddFloatToArray"), FString::Printf(TEXT("Added value %f to array '%s'"), Value, *AccessString));
}

void FEasyJsonObjectV2::AddStringToArray(const FString& AccessString, const FString& Value)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("AddStringToArray(%s, '%s')"), *AccessString, *Value));
	
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	if (Accessers.Num() == 0)
	{
		return;
	}
	
	const FString& FinalAccessor = Accessers.Last();
	// For AddStringToArray, the final accessor should be the array property name
	// (no array index notation expected)
	FString ArrayPropertyName = FinalAccessor;
	
	// Get the parent object - for "numbers" this should be the root object
	// for "user.numbers" this should be the "user" object
	TSharedPtr<FJsonObject> ParentObject;
	if (Accessers.Num() == 1)
	{
		// Direct property on root object
		ParentObject = InnerObject;
	}
	else
	{
		// Nested property - get parent path
		TArray<FString> ParentAccessers = Accessers;
		ParentAccessers.RemoveAt(ParentAccessers.Num() - 1);
		FString ParentPath = FString::Join(ParentAccessers, TEXT("."));
		ParentObject = CreateOrGetObject(ParentPath);
	}
	
	if (!ParentObject.IsValid())
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("PathCreationFailed"), TEXT("Could not create or get parent object"));
		return;
	}
	
	// Get existing array or create new one
	const TArray<TSharedPtr<FJsonValue>>* ExistingArray;
	TArray<TSharedPtr<FJsonValue>> ModifiedArray;
	
	if (ParentObject->TryGetArrayField(ArrayPropertyName, ExistingArray))
	{
		ModifiedArray = *ExistingArray;
	}
	
	// Add the new value
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueString(Value));
	ModifiedArray.Add(NewValue);
	
	ParentObject->SetArrayField(ArrayPropertyName, ModifiedArray);
	
	EASYJSON_DEBUG_SUCCESS(TEXT("AddStringToArray"), FString::Printf(TEXT("Added value '%s' to array '%s'"), *Value, *AccessString));
}

void FEasyJsonObjectV2::AddBoolToArray(const FString& AccessString, bool Value)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("AddBoolToArray(%s, %s)"), *AccessString, Value ? TEXT("true") : TEXT("false")));
	
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	if (Accessers.Num() == 0)
	{
		return;
	}
	
	const FString& FinalAccessor = Accessers.Last();
	// For AddBoolToArray, the final accessor should be the array property name
	// (no array index notation expected)
	FString ArrayPropertyName = FinalAccessor;
	
	// Get the parent object - for "numbers" this should be the root object
	// for "user.numbers" this should be the "user" object
	TSharedPtr<FJsonObject> ParentObject;
	if (Accessers.Num() == 1)
	{
		// Direct property on root object
		ParentObject = InnerObject;
	}
	else
	{
		// Nested property - get parent path
		TArray<FString> ParentAccessers = Accessers;
		ParentAccessers.RemoveAt(ParentAccessers.Num() - 1);
		FString ParentPath = FString::Join(ParentAccessers, TEXT("."));
		ParentObject = CreateOrGetObject(ParentPath);
	}
	
	if (!ParentObject.IsValid())
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("PathCreationFailed"), TEXT("Could not create or get parent object"));
		return;
	}
	
	// Get existing array or create new one
	const TArray<TSharedPtr<FJsonValue>>* ExistingArray;
	TArray<TSharedPtr<FJsonValue>> ModifiedArray;
	
	if (ParentObject->TryGetArrayField(ArrayPropertyName, ExistingArray))
	{
		ModifiedArray = *ExistingArray;
	}
	
	// Add the new value
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueBoolean(Value));
	ModifiedArray.Add(NewValue);
	
	ParentObject->SetArrayField(ArrayPropertyName, ModifiedArray);
	
	EASYJSON_DEBUG_SUCCESS(TEXT("AddBoolToArray"), FString::Printf(TEXT("Added value %s to array '%s'"), Value ? TEXT("true") : TEXT("false"), *AccessString));
}

void FEasyJsonObjectV2::AddObjectToArray(const FString& AccessString, const FEasyJsonObjectV2& Object)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("AddObjectToArray(%s)"), *AccessString));
	
	if (!Object.IsValid())
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("InvalidObject"), TEXT("The object to add is not valid"));
		return;
	}
	
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	if (Accessers.Num() == 0)
	{
		return;
	}
	
	const FString& FinalAccessor = Accessers.Last();
	// For AddObjectToArray, the final accessor should be the array property name
	// (no array index notation expected)
	FString ArrayPropertyName = FinalAccessor;
	
	// Get the parent object - for "numbers" this should be the root object
	// for "user.numbers" this should be the "user" object
	TSharedPtr<FJsonObject> ParentObject;
	if (Accessers.Num() == 1)
	{
		// Direct property on root object
		ParentObject = InnerObject;
	}
	else
	{
		// Nested property - get parent path
		TArray<FString> ParentAccessers = Accessers;
		ParentAccessers.RemoveAt(ParentAccessers.Num() - 1);
		FString ParentPath = FString::Join(ParentAccessers, TEXT("."));
		ParentObject = CreateOrGetObject(ParentPath);
	}
	
	if (!ParentObject.IsValid())
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("PathCreationFailed"), TEXT("Could not create or get parent object"));
		return;
	}
	
	// Get existing array or create new one
	const TArray<TSharedPtr<FJsonValue>>* ExistingArray;
	TArray<TSharedPtr<FJsonValue>> ModifiedArray;
	
	if (ParentObject->TryGetArrayField(ArrayPropertyName, ExistingArray))
	{
		ModifiedArray = *ExistingArray;
	}
	
	// Add the new value
	TSharedPtr<FJsonValue> NewValue = MakeShareable(new FJsonValueObject(Object.InnerObject));
	ModifiedArray.Add(NewValue);
	
	ParentObject->SetArrayField(ArrayPropertyName, ModifiedArray);
	
	EASYJSON_DEBUG_SUCCESS(TEXT("AddObjectToArray"), FString::Printf(TEXT("Added object to array '%s'"), *AccessString));
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
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("ToString(PrettyPrint: %s)"), bPrettyPrint ? TEXT("true") : TEXT("false")));
	
	if (!IsValid())
	{
		EASYJSON_DEBUG_ERROR(TEXT("ToString"), TEXT("InvalidObject"), TEXT("JSON object is not valid"));
		return FString();
	}
	
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = bPrettyPrint 
		? TJsonWriterFactory<>::Create(&OutputString)
		: TJsonWriterFactory<>::Create(&OutputString, 0);
	
	FJsonSerializer::Serialize(InnerObject.ToSharedRef(), Writer);
	
	EASYJSON_DEBUG_SUCCESS(TEXT("ToString"), FString::Printf(TEXT("Generated JSON string (%d characters)"), OutputString.Len()));
	
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
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("ReadEasyJsonValue(%s)"), *AccessString));
	
	if (!IsValid())
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("InvalidObject"), TEXT("JSON object is not valid"));
		return FEasyJsonValueV2();
	}
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	// Log access string parsing
	FEasyJsonV2DebugLogger::LogAccessParsing(AccessString, Accessers);
	
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
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("CreateOrGetObject(%s)"), *AccessString));
	
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	TSharedPtr<FJsonObject> CurrentObject = InnerObject;
	
	for (int32 i = 0; i < Accessers.Num(); ++i)
	{
		const FString& AccessName = Accessers[i];
		
		FString PropertyName;
		int32 ArrayIndex = 0;
		bool bIsArray = IsAccessAsArray(AccessName, PropertyName, ArrayIndex);
		
		EASYJSON_DEBUG_LOG(TEXT("CreateOrGetObject"), TEXT("Processing"), FString::Printf(TEXT("Level %d: %s (Property: %s, IsArray: %s, Index: %d)"), i, *AccessName, *PropertyName, bIsArray ? TEXT("true") : TEXT("false"), ArrayIndex));
		
		// Check if property already exists
		if (!CurrentObject->HasField(PropertyName))
		{
			EASYJSON_DEBUG_LOG(TEXT("CreateOrGetObject"), TEXT("Creating"), FString::Printf(TEXT("Property '%s' does not exist, creating it"), *PropertyName));
			
			// Create new object or array based on the next accessor
			bool bNextIsArray = false;
			if (i + 1 < Accessers.Num())
			{
				FString NextPropertyName;
				int32 NextArrayIndex = 0;
				bNextIsArray = IsAccessAsArray(Accessers[i + 1], NextPropertyName, NextArrayIndex);
			}
			
			if (bIsArray)
			{
				EASYJSON_DEBUG_LOG(TEXT("CreateOrGetObject"), TEXT("Creating"), FString::Printf(TEXT("Creating array '%s' with %d elements"), *PropertyName, ArrayIndex + 1));
				// Create array
				TArray<TSharedPtr<FJsonValue>> NewArray;
				// Expand array to required size
				for (int32 j = 0; j <= ArrayIndex; ++j)
				{
					if (bNextIsArray || i + 1 < Accessers.Num())
					{
						NewArray.Add(MakeShareable(new FJsonValueObject(MakeShareable(new FJsonObject()))));
					}
					else
					{
						NewArray.Add(MakeShareable(new FJsonValueNull()));
					}
				}
				CurrentObject->SetArrayField(PropertyName, NewArray);
			}
			else
			{
				EASYJSON_DEBUG_LOG(TEXT("CreateOrGetObject"), TEXT("Creating"), FString::Printf(TEXT("Creating object '%s'"), *PropertyName));
				// Create object
				TSharedPtr<FJsonObject> NewObject = MakeShareable(new FJsonObject());
				CurrentObject->SetObjectField(PropertyName, NewObject);
			}
		}
		else
		{
			EASYJSON_DEBUG_LOG(TEXT("CreateOrGetObject"), TEXT("Found"), FString::Printf(TEXT("Property '%s' already exists"), *PropertyName));
		}
		
		// Navigate to next level
		if (bIsArray)
		{
			const TArray<TSharedPtr<FJsonValue>>* ArrayValue;
			if (CurrentObject->TryGetArrayField(PropertyName, ArrayValue))
			{
				// Expand array if necessary
				if (ArrayIndex >= ArrayValue->Num())
				{
					// Need to expand array
					TArray<TSharedPtr<FJsonValue>> ExpandedArray = *ArrayValue;
					while (ExpandedArray.Num() <= ArrayIndex)
					{
						ExpandedArray.Add(MakeShareable(new FJsonValueNull()));
					}
					CurrentObject->SetArrayField(PropertyName, ExpandedArray);
					
					// Get updated array
					CurrentObject->TryGetArrayField(PropertyName, ArrayValue);
				}
				
				if (ArrayIndex < ArrayValue->Num())
				{
					if ((*ArrayValue)[ArrayIndex]->Type == EJson::Object)
					{
						const TSharedPtr<FJsonObject>* ObjectPtr;
						if ((*ArrayValue)[ArrayIndex]->TryGetObject(ObjectPtr))
						{
							CurrentObject = *ObjectPtr;
						}
					}
					else
					{
						// Replace with object
						TSharedPtr<FJsonObject> NewObject = MakeShareable(new FJsonObject());
						TArray<TSharedPtr<FJsonValue>> ModifiedArray = *ArrayValue;
						ModifiedArray[ArrayIndex] = MakeShareable(new FJsonValueObject(NewObject));
						CurrentObject->SetArrayField(PropertyName, ModifiedArray);
						CurrentObject = NewObject;
					}
				}
			}
		}
		else
		{
			const TSharedPtr<FJsonObject>* ObjectPtr;
			if (CurrentObject->TryGetObjectField(PropertyName, ObjectPtr))
			{
				CurrentObject = *ObjectPtr;
			}
		}
	}
	
	return CurrentObject;
}

TSharedPtr<FJsonValue> FEasyJsonObjectV2::CreateValue(const FString& AccessString, TSharedPtr<FJsonValue> NewValue)
{
	EASYJSON_DEBUG_SCOPE(FString::Printf(TEXT("CreateValue(%s)"), *AccessString));
	
	if (!IsValid())
	{
		InnerObject = MakeShareable(new FJsonObject());
	}
	
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);
	
	if (Accessers.Num() == 0)
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("EmptyPath"), TEXT("Access string is empty"));
		return nullptr;
	}
	
	// Get the parent object that should contain the final property
	FString ParentPath;
	for (int32 i = 0; i < Accessers.Num() - 1; ++i)
	{
		if (i > 0) ParentPath += TEXT(".");
		ParentPath += Accessers[i];
	}
	
	EASYJSON_DEBUG_LOG(TEXT("CreateValue"), TEXT("Processing"), FString::Printf(TEXT("ParentPath: '%s', FinalProperty: '%s'"), *ParentPath, *Accessers.Last()));
	
	TSharedPtr<FJsonObject> ParentObject;
	if (ParentPath.IsEmpty())
	{
		EASYJSON_DEBUG_LOG(TEXT("CreateValue"), TEXT("Root"), TEXT("Using root object as parent"));
		ParentObject = InnerObject;
	}
	else
	{
		EASYJSON_DEBUG_LOG(TEXT("CreateValue"), TEXT("Calling"), FString::Printf(TEXT("CreateOrGetObject('%s')"), *ParentPath));
		ParentObject = CreateOrGetObject(ParentPath);
	}
	
	if (!ParentObject.IsValid())
	{
		EASYJSON_DEBUG_ERROR(AccessString, TEXT("ParentObjectInvalid"), TEXT("Failed to create or get parent object"));
		return nullptr;
	}
	
	EASYJSON_DEBUG_LOG(TEXT("CreateValue"), TEXT("ParentObject"), TEXT("Successfully obtained parent object"));
	
	// Set the final property
	const FString& FinalAccessor = Accessers.Last();
	FString PropertyName;
	int32 ArrayIndex = 0;
	bool bIsArray = IsAccessAsArray(FinalAccessor, PropertyName, ArrayIndex);
	
	EASYJSON_DEBUG_LOG(TEXT("CreateValue"), TEXT("FinalProperty"), FString::Printf(TEXT("Setting property '%s' (IsArray: %s, Index: %d)"), *PropertyName, bIsArray ? TEXT("true") : TEXT("false"), ArrayIndex));
	
	if (bIsArray)
	{
		EASYJSON_DEBUG_LOG(TEXT("CreateValue"), TEXT("Array"), FString::Printf(TEXT("Setting array element [%d] in property '%s'"), ArrayIndex, *PropertyName));
		// Handle array assignment
		const TArray<TSharedPtr<FJsonValue>>* ExistingArray;
		TArray<TSharedPtr<FJsonValue>> ModifiedArray;
		
		if (ParentObject->TryGetArrayField(PropertyName, ExistingArray))
		{
			ModifiedArray = *ExistingArray;
		}
		
		// Expand array if necessary
		while (ModifiedArray.Num() <= ArrayIndex)
		{
			ModifiedArray.Add(MakeShareable(new FJsonValueNull()));
		}
		
		// Set the value
		ModifiedArray[ArrayIndex] = NewValue;
		ParentObject->SetArrayField(PropertyName, ModifiedArray);
		
		EASYJSON_DEBUG_SUCCESS(TEXT("CreateValue"), FString::Printf(TEXT("Successfully set array element [%d] in property '%s'"), ArrayIndex, *PropertyName));
		return NewValue;
	}
	else
	{
		// Handle direct property assignment
		ParentObject->SetField(PropertyName, NewValue);
		EASYJSON_DEBUG_SUCCESS(TEXT("CreateValue"), FString::Printf(TEXT("Successfully set property '%s'"), *PropertyName));
		return NewValue;
	}
}