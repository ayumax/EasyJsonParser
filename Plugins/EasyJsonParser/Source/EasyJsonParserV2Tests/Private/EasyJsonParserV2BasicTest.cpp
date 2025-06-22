// Copyright 2025 ayumax. All Rights Reserved.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Engine/Engine.h"
#include "EasyJsonObjectV2.h"
#include "EasyJsonParseManagerV2.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2BasicReadTest, "EasyJsonParser.V2.BasicRead", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2BasicReadTest::RunTest(const FString& Parameters)
{
	// Create test JSON string
	const FString TestJson = TEXT(R"({
		"name": "TestUser",
		"age": 25,
		"height": 175.5,
		"active": true,
		"settings": {
			"theme": "dark",
			"notifications": true
		},
		"scores": [100, 85, 92],
		"friends": [
			{"name": "Alice", "age": 23},
			{"name": "Bob", "age": 27}
		]
	})");
	
	// Test loading from string
	bool bSuccess = false;
	FString ErrorMessage;
	FEasyJsonObjectV2 JsonObject = UEasyJsonParseManagerV2::LoadFromString(TestJson, bSuccess, ErrorMessage);
	
	TestTrue("JSON should load successfully", bSuccess);
	TestTrue("JSON object should be valid", JsonObject.IsValid());
	
	// Test basic reads
	TestEqual("Read string value", JsonObject.ReadString("name"), FString("TestUser"));
	TestEqual("Read int value", JsonObject.ReadInt("age"), 25);
	TestEqual("Read float value", JsonObject.ReadFloat("height"), 175.5f);
	TestEqual("Read bool value", JsonObject.ReadBool("active"), true);
	
	// Test nested object reads
	TestEqual("Read nested string", JsonObject.ReadString("settings.theme"), FString("dark"));
	TestEqual("Read nested bool", JsonObject.ReadBool("settings.notifications"), true);
	
	// Test array access
	TestEqual("Read array element", JsonObject.ReadInt("scores[0]"), 100);
	TestEqual("Read array element", JsonObject.ReadInt("scores[1]"), 85);
	TestEqual("Read array element", JsonObject.ReadInt("scores[2]"), 92);
	
	// Test object array access
	TestEqual("Read object array element", JsonObject.ReadString("friends[0].name"), FString("Alice"));
	TestEqual("Read object array element", JsonObject.ReadInt("friends[0].age"), 23);
	TestEqual("Read object array element", JsonObject.ReadString("friends[1].name"), FString("Bob"));
	TestEqual("Read object array element", JsonObject.ReadInt("friends[1].age"), 27);
	
	// Test default values
	TestEqual("Non-existent string returns default", JsonObject.ReadString("missing", "default"), FString("default"));
	TestEqual("Non-existent int returns default", JsonObject.ReadInt("missing", 42), 42);
	TestEqual("Non-existent float returns default", JsonObject.ReadFloat("missing", 3.14f), 3.14f);
	TestEqual("Non-existent bool returns default", JsonObject.ReadBool("missing", true), true);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2ObjectReadTest, "EasyJsonParser.V2.ObjectRead", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2ObjectReadTest::RunTest(const FString& Parameters)
{
	const FString TestJson = TEXT(R"({
		"user": {
			"id": 123,
			"profile": {
				"name": "TestUser",
				"email": "test@example.com"
			}
		},
		"items": [
			{"id": 1, "name": "Item1"},
			{"id": 2, "name": "Item2"}
		]
	})");
	
	bool bSuccess = false;
	FString ErrorMessage;
	FEasyJsonObjectV2 JsonObject = UEasyJsonParseManagerV2::LoadFromString(TestJson, bSuccess, ErrorMessage);
	
	TestTrue("JSON should load successfully", bSuccess);
	
	// Test reading single object
	bool bFound = false;
	FEasyJsonObjectV2 UserObject = JsonObject.ReadObject("user", bFound);
	TestTrue("User object should be found", bFound);
	TestTrue("User object should be valid", UserObject.IsValid());
	TestEqual("Read from returned object", UserObject.ReadInt("id"), 123);
	
	// Test reading nested object
	FEasyJsonObjectV2 ProfileObject = JsonObject.ReadObject("user.profile", bFound);
	TestTrue("Profile object should be found", bFound);
	TestEqual("Read from nested object", ProfileObject.ReadString("name"), FString("TestUser"));
	TestEqual("Read from nested object", ProfileObject.ReadString("email"), FString("test@example.com"));
	
	// Test reading object array
	TArray<FEasyJsonObjectV2> ItemsArray = JsonObject.ReadObjects("items", bFound);
	TestTrue("Items array should be found", bFound);
	TestEqual("Items array size", ItemsArray.Num(), 2);
	
	if (ItemsArray.Num() >= 2)
	{
		TestEqual("First item id", ItemsArray[0].ReadInt("id"), 1);
		TestEqual("First item name", ItemsArray[0].ReadString("name"), FString("Item1"));
		TestEqual("Second item id", ItemsArray[1].ReadInt("id"), 2);
		TestEqual("Second item name", ItemsArray[1].ReadString("name"), FString("Item2"));
	}
	
	// Test non-existent object
	FEasyJsonObjectV2 MissingObject = JsonObject.ReadObject("missing", bFound);
	TestFalse("Missing object should not be found", bFound);
	TestFalse("Missing object should not be valid", MissingObject.IsValid());
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2CreateAndConvertTest, "EasyJsonParser.V2.CreateAndConvert", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2CreateAndConvertTest::RunTest(const FString& Parameters)
{
	// Test creating empty object
	FEasyJsonObjectV2 EmptyObject = FEasyJsonObjectV2::CreateEmpty();
	TestTrue("Empty object should be valid", EmptyObject.IsValid());
	
	// Test converting to string (empty object)
	FString JsonString = EmptyObject.ToString();
	// Remove newlines and spaces for comparison
	JsonString.ReplaceInline(TEXT("\n"), TEXT(""));
	JsonString.ReplaceInline(TEXT("\r"), TEXT(""));
	JsonString.ReplaceInline(TEXT("\t"), TEXT(""));
	JsonString.ReplaceInline(TEXT(" "), TEXT(""));
	TestEqual("Empty object string", JsonString, FString("{}"));
	
	// Test pretty print
	FString PrettyString = EmptyObject.ToString(true);
	TestTrue("Pretty print should contain newlines", PrettyString.Contains("\n") || PrettyString.Equals("{}"));
	
	// Test creating from invalid JSON
	bool bSuccess = false;
	FEasyJsonObjectV2 InvalidObject = FEasyJsonObjectV2::CreateFromString("invalid json", bSuccess);
	TestFalse("Invalid JSON should fail", bSuccess);
	TestFalse("Invalid object should not be valid", InvalidObject.IsValid());
	
	// Test round-trip conversion
	const FString TestJson = TEXT(R"({"test":123,"nested":{"value":"hello"}})");
	FEasyJsonObjectV2 RoundTripObject = FEasyJsonObjectV2::CreateFromString(TestJson, bSuccess);
	TestTrue("Round-trip object should load", bSuccess);
	
	FString ConvertedJson = RoundTripObject.ToString(false);
	FEasyJsonObjectV2 ReloadedObject = FEasyJsonObjectV2::CreateFromString(ConvertedJson, bSuccess);
	TestTrue("Reloaded object should load", bSuccess);
	TestEqual("Values should match after round-trip", ReloadedObject.ReadInt("test"), 123);
	TestEqual("Nested values should match after round-trip", ReloadedObject.ReadString("nested.value"), FString("hello"));
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2PerformanceTest, "EasyJsonParser.V2.Performance", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2PerformanceTest::RunTest(const FString& Parameters)
{
	// Create a large JSON for performance testing
	const int32 ItemCount = 1000;
	FString LargeJson = TEXT("{\"items\":[");
	
	for (int32 i = 0; i < ItemCount; ++i)
	{
		if (i > 0) LargeJson += TEXT(",");
		LargeJson += FString::Printf(TEXT("{\"id\":%d,\"name\":\"Item%d\",\"value\":%d}"), i, i, i * 10);
	}
	LargeJson += TEXT("]}");
	
	// Measure creation time
	double StartTime = FPlatformTime::Seconds();
	
	bool bSuccess = false;
	FString ErrorMessage;
	FEasyJsonObjectV2 JsonObject = UEasyJsonParseManagerV2::LoadFromString(LargeJson, bSuccess, ErrorMessage);
	
	double LoadTime = FPlatformTime::Seconds() - StartTime;
	
	TestTrue("Large JSON should load successfully", bSuccess);
	TestTrue("Load time should be reasonable", LoadTime < 1.0); // Should load in less than 1 second
	
	// Measure read performance
	StartTime = FPlatformTime::Seconds();
	
	int32 TotalValue = 0;
	for (int32 i = 0; i < ItemCount; ++i)
	{
		TotalValue += JsonObject.ReadInt(FString::Printf(TEXT("items[%d].value"), i));
	}
	
	double ReadTime = FPlatformTime::Seconds() - StartTime;
	
	TestTrue("Read time should be reasonable", ReadTime < 1.0); // Should read all values in less than 1 second
	TestEqual("Total value calculation", TotalValue, (ItemCount - 1) * ItemCount * 10 / 2); // Sum formula
	
	// Log performance results
	UE_LOG(LogTemp, Display, TEXT("V2 Performance - Load %d items: %f seconds"), ItemCount, LoadTime);
	UE_LOG(LogTemp, Display, TEXT("V2 Performance - Read %d values: %f seconds"), ItemCount, ReadTime);
	
	// Test multiple object creation (memory efficiency)
	StartTime = FPlatformTime::Seconds();
	
	const FString SimpleJson = TEXT(R"({"test":123})");
	TArray<FEasyJsonObjectV2> ObjectArray;
	ObjectArray.Reserve(100);
	
	for (int32 i = 0; i < 100; ++i)
	{
		ObjectArray.Add(FEasyJsonObjectV2::CreateFromString(SimpleJson, bSuccess));
	}
	
	double CreateTime = FPlatformTime::Seconds() - StartTime;
	TestTrue("Multiple object creation should be fast", CreateTime < 0.1); // Should create 100 objects in less than 0.1 seconds
	
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS