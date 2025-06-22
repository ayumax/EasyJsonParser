// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Engine/Engine.h"
#include "EasyJsonObjectV2.h"
#include "EasyJsonParseManagerV2.h"
#include "EasyJsonParserV2Debug.h"

#if WITH_DEV_AUTOMATION_TESTS

// 1. Debug Configuration Testing
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2DebugConfigTest, "EasyJsonParser.V2.Debug.Configuration", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2DebugConfigTest::RunTest(const FString& Parameters)
{
	// Save original state
	bool bOriginalDebugMode = ::EasyJsonParserV2Debug::IsDebugEnabled();
	EEasyJsonParserV2DebugLogLevel OriginalLogLevel = ::EasyJsonParserV2Debug::GetDebugLogLevel();
	
	// Test enabling/disabling debug mode
	::EasyJsonParserV2Debug::SetDebugEnabled(true);
	bool bDebugEnabled = ::EasyJsonParserV2Debug::IsDebugEnabled();
	TestTrue("Debug mode should be enabled", bDebugEnabled);
	
	::EasyJsonParserV2Debug::SetDebugEnabled(false);
	bool bDebugDisabled = ::EasyJsonParserV2Debug::IsDebugEnabled();
	TestFalse("Debug mode should be disabled", bDebugDisabled);
	
	// Test debug log level settings
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Basic);
	EEasyJsonParserV2DebugLogLevel BasicLevel = ::EasyJsonParserV2Debug::GetDebugLogLevel();
	TestEqual("Debug log level should be Basic", BasicLevel, EEasyJsonParserV2DebugLogLevel::Basic);
	
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Detailed);
	EEasyJsonParserV2DebugLogLevel DetailedLevel = ::EasyJsonParserV2Debug::GetDebugLogLevel();
	TestEqual("Debug log level should be Detailed", DetailedLevel, EEasyJsonParserV2DebugLogLevel::Detailed);
	
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Verbose);
	EEasyJsonParserV2DebugLogLevel VerboseLevel = ::EasyJsonParserV2Debug::GetDebugLogLevel();
	TestEqual("Debug log level should be Verbose", VerboseLevel, EEasyJsonParserV2DebugLogLevel::Verbose);
	
	// Restore original state
	::EasyJsonParserV2Debug::SetDebugEnabled(bOriginalDebugMode);
	::EasyJsonParserV2Debug::SetDebugLogLevel(OriginalLogLevel);
	
	return true;
}

// 2. Basic Property Access with Debug Logging
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2DebugBasicTest, "EasyJsonParser.V2.Debug.BasicAccess", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2DebugBasicTest::RunTest(const FString& Parameters)
{
	// Save original state
	bool bOriginalDebugMode = ::EasyJsonParserV2Debug::IsDebugEnabled();
	EEasyJsonParserV2DebugLogLevel OriginalLogLevel = ::EasyJsonParserV2Debug::GetDebugLogLevel();
	
	// Enable debug mode for testing
	::EasyJsonParserV2Debug::SetDebugEnabled(true);
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Verbose);
	
	// Create JSON object
	FEasyJsonObjectV2 JsonObject = FEasyJsonObjectV2::CreateEmpty();
	TestTrue("Empty object should be valid", JsonObject.IsValid());
	
	// Test basic property write and read (should log debug info)
	JsonObject.WriteString("name", "TestUser");
	FString ReadName = JsonObject.ReadString("name");
	TestEqual("Direct write should work", ReadName, FString("TestUser"));
	
	// Test different data types with debug logging
	JsonObject.WriteInt("age", 25);
	int32 ReadAge = JsonObject.ReadInt("age");
	TestEqual("Int write/read should work", ReadAge, 25);
	
	JsonObject.WriteFloat("score", 98.5f);
	float ReadScore = JsonObject.ReadFloat("score");
	TestEqual("Float write/read should work", ReadScore, 98.5f);
	
	JsonObject.WriteBool("active", true);
	bool ReadActive = JsonObject.ReadBool("active");
	TestTrue("Bool write/read should work", ReadActive);
	
	// Restore original state
	::EasyJsonParserV2Debug::SetDebugEnabled(bOriginalDebugMode);
	::EasyJsonParserV2Debug::SetDebugLogLevel(OriginalLogLevel);
	
	return true;
}

// 3. Nested Property Access Debug
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2DebugNestedTest, "EasyJsonParser.V2.Debug.NestedAccess", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2DebugNestedTest::RunTest(const FString& Parameters)
{
	// Save original state
	bool bOriginalDebugMode = ::EasyJsonParserV2Debug::IsDebugEnabled();
	EEasyJsonParserV2DebugLogLevel OriginalLogLevel = ::EasyJsonParserV2Debug::GetDebugLogLevel();
	
	// Enable debug mode for testing
	::EasyJsonParserV2Debug::SetDebugEnabled(true);
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Verbose);
	
	// Create JSON object
	FEasyJsonObjectV2 JsonObject = FEasyJsonObjectV2::CreateEmpty();
	
	// Test nested property write (should log detailed access parsing)
	JsonObject.WriteString("user.profile.name", "NestedUser");
	FString ReadNestedName = JsonObject.ReadString("user.profile.name");
	TestEqual("Nested write should work", ReadNestedName, FString("NestedUser"));
	
	// Test deeper nesting
	JsonObject.WriteString("data.section.subsection.value", "DeepValue");
	FString ReadDeepValue = JsonObject.ReadString("data.section.subsection.value");
	TestEqual("Deep nested write should work", ReadDeepValue, FString("DeepValue"));
	
	// Test nested object with different types
	JsonObject.WriteInt("config.settings.timeout", 30);
	int32 ReadTimeout = JsonObject.ReadInt("config.settings.timeout");
	TestEqual("Nested int write should work", ReadTimeout, 30);
	
	// Restore original state
	::EasyJsonParserV2Debug::SetDebugEnabled(bOriginalDebugMode);
	::EasyJsonParserV2Debug::SetDebugLogLevel(OriginalLogLevel);
	
	return true;
}

// 4. Array Access Debug Logging
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2DebugArrayTest, "EasyJsonParser.V2.Debug.ArrayAccess", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2DebugArrayTest::RunTest(const FString& Parameters)
{
	// Save original state
	bool bOriginalDebugMode = ::EasyJsonParserV2Debug::IsDebugEnabled();
	EEasyJsonParserV2DebugLogLevel OriginalLogLevel = ::EasyJsonParserV2Debug::GetDebugLogLevel();
	
	// Enable debug mode for testing
	::EasyJsonParserV2Debug::SetDebugEnabled(true);
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Verbose);
	
	// Create JSON object
	FEasyJsonObjectV2 JsonObject = FEasyJsonObjectV2::CreateEmpty();
	
	// Test array access (should log array parsing)
	JsonObject.WriteString("users[0].name", "FirstUser");
	FString FirstUserName = JsonObject.ReadString("users[0].name");
	TestEqual("Array access should work", FirstUserName, FString("FirstUser"));
	
	// Test multiple array elements
	JsonObject.WriteString("users[1].name", "SecondUser");
	FString SecondUserName = JsonObject.ReadString("users[1].name");
	TestEqual("Second array element should work", SecondUserName, FString("SecondUser"));
	
	// Test nested array access
	JsonObject.WriteInt("data[0].values[2]", 42);
	int32 NestedArrayValue = JsonObject.ReadInt("data[0].values[2]");
	TestEqual("Nested array access should work", NestedArrayValue, 42);
	
	// Restore original state
	::EasyJsonParserV2Debug::SetDebugEnabled(bOriginalDebugMode);
	::EasyJsonParserV2Debug::SetDebugLogLevel(OriginalLogLevel);
	
	return true;
}

// 5. Performance Scope Testing
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2DebugScopeTest, "EasyJsonParser.V2.Debug.PerformanceScope", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2DebugScopeTest::RunTest(const FString& Parameters)
{
	// Save original state
	bool bOriginalDebugMode = ::EasyJsonParserV2Debug::IsDebugEnabled();
	EEasyJsonParserV2DebugLogLevel OriginalLogLevel = ::EasyJsonParserV2Debug::GetDebugLogLevel();
	
	// Enable debug mode for testing
	::EasyJsonParserV2Debug::SetDebugEnabled(true);
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Verbose);
	
	// Create JSON object
	FEasyJsonObjectV2 JsonObject = FEasyJsonObjectV2::CreateEmpty();
	
	// Test performance scope with manual scope
	{
		EASYJSON_DEBUG_SCOPE("ComplexOperation");
		
		// Simulate some work
		for (int32 i = 0; i < 5; ++i)
		{
			JsonObject.WriteInt(FString::Printf(TEXT("data[%d].value"), i), i * 10);
		}
		
		// Verify the operations worked
		for (int32 i = 0; i < 5; ++i)
		{
			int32 Value = JsonObject.ReadInt(FString::Printf(TEXT("data[%d].value"), i));
			TestEqual(FString::Printf(TEXT("Array element %d should be correct"), i), Value, i * 10);
		}
	}
	
	// Test nested scopes
	{
		EASYJSON_DEBUG_SCOPE("NestedScopeTest");
		JsonObject.WriteString("nested.scope.test", "ScopeValue");
		FString ScopeValue = JsonObject.ReadString("nested.scope.test");
		TestEqual("Nested scope operation should work", ScopeValue, FString("ScopeValue"));
	}
	
	// Restore original state
	::EasyJsonParserV2Debug::SetDebugEnabled(bOriginalDebugMode);
	::EasyJsonParserV2Debug::SetDebugLogLevel(OriginalLogLevel);
	
	return true;
}

// 6. Direct Debug Logger Testing
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2DebugLoggerTest, "EasyJsonParser.V2.Debug.DirectLogger", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2DebugLoggerTest::RunTest(const FString& Parameters)
{
	// Save original state
	bool bOriginalDebugMode = ::EasyJsonParserV2Debug::IsDebugEnabled();
	EEasyJsonParserV2DebugLogLevel OriginalLogLevel = ::EasyJsonParserV2Debug::GetDebugLogLevel();
	
	// Enable debug mode for testing
	::EasyJsonParserV2Debug::SetDebugEnabled(true);
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Verbose);
	
	// Test debug logging methods directly
	FEasyJsonV2DebugLogger::LogSuccess("TestOperation", "All operations completed successfully");
	FEasyJsonV2DebugLogger::LogOperation("JsonRead", "Success", "Read operation completed");
	
	// Test different log levels
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Basic);
	FEasyJsonV2DebugLogger::LogSuccess("BasicLevelTest", "This should appear in Basic level");
	
	::EasyJsonParserV2Debug::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Detailed);
	FEasyJsonV2DebugLogger::LogOperation("DetailedTest", "Info", "This should appear in Detailed level");
	
	// Test that the logger functions can be called without errors
	TestTrue("Direct logger calls should complete without errors", true);
	
	// Restore original state
	::EasyJsonParserV2Debug::SetDebugEnabled(bOriginalDebugMode);
	::EasyJsonParserV2Debug::SetDebugLogLevel(OriginalLogLevel);
	
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS