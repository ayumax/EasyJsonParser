// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Engine/Engine.h"
#include "EasyJsonObjectV2.h"
#include "EasyJsonParseManagerV2.h"
#include "EasyJsonParserV2Debug.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2DebugTest, "EasyJsonParser.V2.Debug", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2DebugTest::RunTest(const FString& Parameters)
{
	// Enable debug mode for testing using namespace functions
	::EasyJsonParserV2Debug::SetDebugEnabled(true);
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Verbose);
	
	// Test debug logging with JSON operations
	FEasyJsonObjectV2 JsonObject = FEasyJsonObjectV2::CreateEmpty();
	TestTrue("Empty object should be valid", JsonObject.IsValid());
	
	// Test direct property write (should log debug info)
	JsonObject.WriteString("name", "TestUser");
	FString ReadName = JsonObject.ReadString("name");
	UE_LOG(LogTemp, Warning, TEXT("Debug: Wrote 'TestUser', Read '%s'"), *ReadName);
	TestEqual("Direct write should work", ReadName, FString("TestUser"));
	
	// Test invalid access (should log error)
	int32 InvalidValue = JsonObject.ReadInt("nonexistent.path", -1);
	TestEqual("Invalid access should return default", InvalidValue, -1);
	
	// Test nested write (should log detailed access parsing)
	JsonObject.WriteString("user.profile.name", "NestedUser");
	FString ReadNestedName = JsonObject.ReadString("user.profile.name");
	UE_LOG(LogTemp, Warning, TEXT("Debug: Wrote nested 'NestedUser', Read '%s'"), *ReadNestedName);
	TestEqual("Nested write should work", ReadNestedName, FString("NestedUser"));
	
	// Test array access (should log array parsing)
	JsonObject.WriteString("users[0].name", "FirstUser");
	FString FirstUserName = JsonObject.ReadString("users[0].name");
	TestEqual("Array access should work", FirstUserName, FString("FirstUser"));
	
	// Test performance scope with manual scope
	{
		EASYJSON_DEBUG_SCOPE("ComplexOperation");
		
		// Simulate some work
		for (int32 i = 0; i < 5; ++i)
		{
			JsonObject.WriteInt(FString::Printf(TEXT("data[%d].value"), i), i * 10);
		}
	}
	
	// Test debug logging methods directly
	FEasyJsonV2DebugLogger::LogSuccess("TestOperation", "All operations completed successfully");
	FEasyJsonV2DebugLogger::LogOperation("JsonRead", "Success", "Read operation completed");
	
	// Disable debug mode after testing
	::EasyJsonParserV2Debug::SetDebugEnabled(false);
	
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS