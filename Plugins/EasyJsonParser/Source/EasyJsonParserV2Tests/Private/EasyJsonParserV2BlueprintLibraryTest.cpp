// Copyright 2025 ayumax. All Rights Reserved.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Engine/Engine.h"
#include "EasyJsonParserV2BlueprintLibrary.h"

#if WITH_DEV_AUTOMATION_TESTS

// 1. Basic JSON Creation and Read/Write Operations
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2BlueprintLibraryBasicTest, "EasyJsonParser.V2.BlueprintLibrary.Basic", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2BlueprintLibraryBasicTest::RunTest(const FString& Parameters)
{
	// Test JSON creation and basic operations through Blueprint library
	FEasyJsonObjectV2 JsonObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	TestTrue("Empty JSON object should be valid", UEasyJsonParserV2BlueprintLibrary::IsJsonObjectValid(JsonObject));
	
	// Test writing values through Blueprint library
	UEasyJsonParserV2BlueprintLibrary::WriteString(JsonObject, "name", "BlueprintUser");
	UEasyJsonParserV2BlueprintLibrary::WriteInt(JsonObject, "age", 25);
	UEasyJsonParserV2BlueprintLibrary::WriteFloat(JsonObject, "score", 98.5f);
	UEasyJsonParserV2BlueprintLibrary::WriteBool(JsonObject, "active", true);
	
	// Test reading values through Blueprint library
	FString Name = UEasyJsonParserV2BlueprintLibrary::ReadString(JsonObject, "name", "");
	int32 Age = UEasyJsonParserV2BlueprintLibrary::ReadInt(JsonObject, "age", 0);
	float Score = UEasyJsonParserV2BlueprintLibrary::ReadFloat(JsonObject, "score", 0.0f);
	bool bActive = UEasyJsonParserV2BlueprintLibrary::ReadBool(JsonObject, "active", false);
	
	TestEqual("Name should be read correctly", Name, FString("BlueprintUser"));
	TestEqual("Age should be read correctly", Age, 25);
	TestEqual("Score should be read correctly", Score, 98.5f);
	TestTrue("Active should be read correctly", bActive);
	
	return true;
}

// 2. Array Operations
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2BlueprintLibraryArrayTest, "EasyJsonParser.V2.BlueprintLibrary.Arrays", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2BlueprintLibraryArrayTest::RunTest(const FString& Parameters)
{
	FEasyJsonObjectV2 JsonObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	
	// Test array operations through Blueprint library
	UEasyJsonParserV2BlueprintLibrary::AddStringToArray(JsonObject, "hobbies", "Reading");
	UEasyJsonParserV2BlueprintLibrary::AddStringToArray(JsonObject, "hobbies", "Gaming");
	UEasyJsonParserV2BlueprintLibrary::AddIntToArray(JsonObject, "scores", 100);
	UEasyJsonParserV2BlueprintLibrary::AddIntToArray(JsonObject, "scores", 95);
	
	return true;
}

// 3. Nested Objects
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2BlueprintLibraryNestedTest, "EasyJsonParser.V2.BlueprintLibrary.Nested", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2BlueprintLibraryNestedTest::RunTest(const FString& Parameters)
{
	FEasyJsonObjectV2 JsonObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	
	// Test nested object operations
	FEasyJsonObjectV2 NestedObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	UEasyJsonParserV2BlueprintLibrary::WriteString(NestedObject, "street", "123 Main St");
	UEasyJsonParserV2BlueprintLibrary::WriteString(NestedObject, "city", "Anytown");
	UEasyJsonParserV2BlueprintLibrary::WriteObject(JsonObject, "address", NestedObject);
	
	// Test reading nested values
	FString Street = UEasyJsonParserV2BlueprintLibrary::ReadString(JsonObject, "address.street", "");
	FString City = UEasyJsonParserV2BlueprintLibrary::ReadString(JsonObject, "address.city", "");
	
	TestEqual("Nested street should be read correctly", Street, FString("123 Main St"));
	TestEqual("Nested city should be read correctly", City, FString("Anytown"));
	
	return true;
}

// 4. JSON String Conversion
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2BlueprintLibraryStringTest, "EasyJsonParser.V2.BlueprintLibrary.StringConversion", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2BlueprintLibraryStringTest::RunTest(const FString& Parameters)
{
	// Create a complete JSON object for testing
	FEasyJsonObjectV2 JsonObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	UEasyJsonParserV2BlueprintLibrary::WriteString(JsonObject, "name", "BlueprintUser");
	UEasyJsonParserV2BlueprintLibrary::WriteInt(JsonObject, "age", 25);
	UEasyJsonParserV2BlueprintLibrary::WriteFloat(JsonObject, "score", 98.5f);
	UEasyJsonParserV2BlueprintLibrary::WriteBool(JsonObject, "active", true);
	
	// Add arrays
	UEasyJsonParserV2BlueprintLibrary::AddStringToArray(JsonObject, "hobbies", "Reading");
	UEasyJsonParserV2BlueprintLibrary::AddStringToArray(JsonObject, "hobbies", "Gaming");
	UEasyJsonParserV2BlueprintLibrary::AddIntToArray(JsonObject, "scores", 100);
	UEasyJsonParserV2BlueprintLibrary::AddIntToArray(JsonObject, "scores", 95);
	
	// Add nested object
	FEasyJsonObjectV2 NestedObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	UEasyJsonParserV2BlueprintLibrary::WriteString(NestedObject, "street", "123 Main St");
	UEasyJsonParserV2BlueprintLibrary::WriteString(NestedObject, "city", "Anytown");
	UEasyJsonParserV2BlueprintLibrary::WriteObject(JsonObject, "address", NestedObject);
	
	// Test JSON string conversion
	FString JsonString = UEasyJsonParserV2BlueprintLibrary::JsonToString(JsonObject, true);
	TestTrue("JSON string should not be empty", !JsonString.IsEmpty());
	UE_LOG(LogTemp, Warning, TEXT("Generated JSON: %s"), *JsonString);
	
	return true;
}

// 5. JSON Loading from String
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2BlueprintLibraryLoadTest, "EasyJsonParser.V2.BlueprintLibrary.LoadFromString", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2BlueprintLibraryLoadTest::RunTest(const FString& Parameters)
{
	// Create a complete JSON object for testing
	FEasyJsonObjectV2 JsonObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	UEasyJsonParserV2BlueprintLibrary::WriteString(JsonObject, "name", "BlueprintUser");
	UEasyJsonParserV2BlueprintLibrary::WriteInt(JsonObject, "age", 25);
	UEasyJsonParserV2BlueprintLibrary::WriteFloat(JsonObject, "score", 98.5f);
	UEasyJsonParserV2BlueprintLibrary::WriteBool(JsonObject, "active", true);
	
	// Add arrays
	UEasyJsonParserV2BlueprintLibrary::AddStringToArray(JsonObject, "hobbies", "Reading");
	UEasyJsonParserV2BlueprintLibrary::AddStringToArray(JsonObject, "hobbies", "Gaming");
	UEasyJsonParserV2BlueprintLibrary::AddIntToArray(JsonObject, "scores", 100);
	UEasyJsonParserV2BlueprintLibrary::AddIntToArray(JsonObject, "scores", 95);
	
	// Add nested object
	FEasyJsonObjectV2 NestedObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	UEasyJsonParserV2BlueprintLibrary::WriteString(NestedObject, "street", "123 Main St");
	UEasyJsonParserV2BlueprintLibrary::WriteString(NestedObject, "city", "Anytown");
	UEasyJsonParserV2BlueprintLibrary::WriteObject(JsonObject, "address", NestedObject);
	
	// Convert to string
	FString JsonString = UEasyJsonParserV2BlueprintLibrary::JsonToString(JsonObject, true);
	
	// Test loading from string through Blueprint library
	bool bSuccess;
	FString ErrorMessage;
	FEasyJsonObjectV2 LoadedObject = UEasyJsonParserV2BlueprintLibrary::LoadJsonFromString(JsonString, bSuccess, ErrorMessage);
	TestTrue("Loading from string should succeed", bSuccess);
	TestTrue("Loaded object should be valid", UEasyJsonParserV2BlueprintLibrary::IsJsonObjectValid(LoadedObject));
	
	// Verify loaded data
	FString LoadedName = UEasyJsonParserV2BlueprintLibrary::ReadString(LoadedObject, "name", "");
	TestEqual("Loaded name should match", LoadedName, FString("BlueprintUser"));
	
	return true;
}

// 6. JSON Equality Comparison (The problematic test)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2BlueprintLibraryEqualityTest, "EasyJsonParser.V2.BlueprintLibrary.Equality", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2BlueprintLibraryEqualityTest::RunTest(const FString& Parameters)
{
	// Create a complete JSON object for testing
	FEasyJsonObjectV2 JsonObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	UEasyJsonParserV2BlueprintLibrary::WriteString(JsonObject, "name", "BlueprintUser");
	UEasyJsonParserV2BlueprintLibrary::WriteInt(JsonObject, "age", 25);
	UEasyJsonParserV2BlueprintLibrary::WriteFloat(JsonObject, "score", 98.5f);
	UEasyJsonParserV2BlueprintLibrary::WriteBool(JsonObject, "active", true);
	
	// Add arrays
	UEasyJsonParserV2BlueprintLibrary::AddStringToArray(JsonObject, "hobbies", "Reading");
	UEasyJsonParserV2BlueprintLibrary::AddStringToArray(JsonObject, "hobbies", "Gaming");
	UEasyJsonParserV2BlueprintLibrary::AddIntToArray(JsonObject, "scores", 100);
	UEasyJsonParserV2BlueprintLibrary::AddIntToArray(JsonObject, "scores", 95);
	
	// Add nested object
	FEasyJsonObjectV2 NestedObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	UEasyJsonParserV2BlueprintLibrary::WriteString(NestedObject, "street", "123 Main St");
	UEasyJsonParserV2BlueprintLibrary::WriteString(NestedObject, "city", "Anytown");
	UEasyJsonParserV2BlueprintLibrary::WriteObject(JsonObject, "address", NestedObject);
	
	// Convert to string and load back
	FString JsonString = UEasyJsonParserV2BlueprintLibrary::JsonToString(JsonObject, true);
	bool bSuccess;
	FString ErrorMessage;
	FEasyJsonObjectV2 LoadedObject = UEasyJsonParserV2BlueprintLibrary::LoadJsonFromString(JsonString, bSuccess, ErrorMessage);
	
	// Debug output for comparison
	FString OriginalCompact = UEasyJsonParserV2BlueprintLibrary::JsonToString(JsonObject, false);
	FString LoadedCompact = UEasyJsonParserV2BlueprintLibrary::JsonToString(LoadedObject, false);
	
	UE_LOG(LogTemp, Warning, TEXT("EQUALITY TEST DEBUG:"));
	UE_LOG(LogTemp, Warning, TEXT("Original (compact): %s"), *OriginalCompact);
	UE_LOG(LogTemp, Warning, TEXT("Loaded (compact): %s"), *LoadedCompact);
	UE_LOG(LogTemp, Warning, TEXT("String equality: %s"), (OriginalCompact == LoadedCompact) ? TEXT("true") : TEXT("false"));
	
	// Test equality comparison
	bool bAreEqual = UEasyJsonParserV2BlueprintLibrary::AreJsonObjectsEqual(JsonObject, LoadedObject);
	UE_LOG(LogTemp, Warning, TEXT("AreJsonObjectsEqual result: %s"), bAreEqual ? TEXT("true") : TEXT("false"));
	
	TestTrue("Original and loaded objects should be equal", bAreEqual);
	
	return true;
}

// 7. Debug Functionality (simplified to avoid error logs)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2BlueprintLibraryDebugTest, "EasyJsonParser.V2.BlueprintLibrary.Debug", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2BlueprintLibraryDebugTest::RunTest(const FString& Parameters)
{
	// Save current debug state
	bool bOriginalDebugMode = UEasyJsonParserV2BlueprintLibrary::IsDebugMode();
	EEasyJsonParserV2DebugLogLevel OriginalLogLevel = UEasyJsonParserV2BlueprintLibrary::GetDebugLogLevel();
	
	// Create test object
	FEasyJsonObjectV2 JsonObject = UEasyJsonParserV2BlueprintLibrary::CreateEmptyJsonObject();
	UEasyJsonParserV2BlueprintLibrary::WriteString(JsonObject, "name", "BlueprintUser");
	
	// Test basic debug functionality
	UEasyJsonParserV2BlueprintLibrary::SetDebugMode(true);
	bool bDebugModeEnabled = UEasyJsonParserV2BlueprintLibrary::IsDebugMode();
	TestTrue("Debug mode should be enabled", bDebugModeEnabled);
	
	UEasyJsonParserV2BlueprintLibrary::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Detailed);
	EEasyJsonParserV2DebugLogLevel CurrentLevel = UEasyJsonParserV2BlueprintLibrary::GetDebugLogLevel();
	TestEqual("Debug log level should be set correctly", CurrentLevel, EEasyJsonParserV2DebugLogLevel::Detailed);
	
	// Test successful read operation with debug enabled
	FString DebugName = UEasyJsonParserV2BlueprintLibrary::ReadString(JsonObject, "name", "");
	TestEqual("Debug read should work correctly", DebugName, FString("BlueprintUser"));
	
	// Test that debug functions can be called without errors
	UEasyJsonParserV2BlueprintLibrary::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Basic);
	UEasyJsonParserV2BlueprintLibrary::SetDebugMode(false);
	
	// Restore original debug state
	UEasyJsonParserV2BlueprintLibrary::SetDebugMode(bOriginalDebugMode);
	UEasyJsonParserV2BlueprintLibrary::SetDebugLogLevel(OriginalLogLevel);
	
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS