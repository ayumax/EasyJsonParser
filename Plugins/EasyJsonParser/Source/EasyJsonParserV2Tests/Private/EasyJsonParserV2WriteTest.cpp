// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Engine/Engine.h"
#include "EasyJsonObjectV2.h"
#include "EasyJsonParseManagerV2.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2BasicWriteTest, "EasyJsonParser.V2.BasicWrite", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2BasicWriteTest::RunTest(const FString& Parameters)
{
	// Create empty JSON object
	FEasyJsonObjectV2 JsonObject = FEasyJsonObjectV2::CreateEmpty();
	TestTrue("Empty object should be valid", JsonObject.IsValid());
	
	// Test basic writes
	JsonObject.WriteString("name", "TestUser");
	JsonObject.WriteInt("age", 25);
	JsonObject.WriteFloat("height", 175.5f);
	JsonObject.WriteBool("active", true);
	
	// Verify written values
	TestEqual("Read written string", JsonObject.ReadString("name"), FString("TestUser"));
	TestEqual("Read written int", JsonObject.ReadInt("age"), 25);
	TestEqual("Read written float", JsonObject.ReadFloat("height"), 175.5f);
	TestEqual("Read written bool", JsonObject.ReadBool("active"), true);
	
	// Test nested object writes
	JsonObject.WriteString("settings.theme", "dark");
	JsonObject.WriteInt("settings.volume", 80);
	JsonObject.WriteBool("settings.notifications", true);
	
	// Verify nested values
	TestEqual("Read nested string", JsonObject.ReadString("settings.theme"), FString("dark"));
	TestEqual("Read nested int", JsonObject.ReadInt("settings.volume"), 80);
	TestEqual("Read nested bool", JsonObject.ReadBool("settings.notifications"), true);
	
	// Test array writes
	JsonObject.WriteInt("scores[0]", 100);
	JsonObject.WriteInt("scores[1]", 85);
	JsonObject.WriteInt("scores[2]", 92);
	
	// Verify array values
	TestEqual("Read array element 0", JsonObject.ReadInt("scores[0]"), 100);
	TestEqual("Read array element 1", JsonObject.ReadInt("scores[1]"), 85);
	TestEqual("Read array element 2", JsonObject.ReadInt("scores[2]"), 92);
	
	// Test object array writes
	JsonObject.WriteString("friends[0].name", "Alice");
	JsonObject.WriteInt("friends[0].age", 23);
	JsonObject.WriteString("friends[1].name", "Bob");
	JsonObject.WriteInt("friends[1].age", 27);
	
	// Verify object array values
	TestEqual("Read object array element", JsonObject.ReadString("friends[0].name"), FString("Alice"));
	TestEqual("Read object array element", JsonObject.ReadInt("friends[0].age"), 23);
	TestEqual("Read object array element", JsonObject.ReadString("friends[1].name"), FString("Bob"));
	TestEqual("Read object array element", JsonObject.ReadInt("friends[1].age"), 27);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2ArrayManipulationTest, "EasyJsonParser.V2.ArrayManipulation", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2ArrayManipulationTest::RunTest(const FString& Parameters)
{
	FEasyJsonObjectV2 JsonObject = FEasyJsonObjectV2::CreateEmpty();
	
	// Test adding to arrays
	JsonObject.AddIntToArray("numbers", 10);
	JsonObject.AddIntToArray("numbers", 20);
	JsonObject.AddIntToArray("numbers", 30);
	
	// Verify array contents
	TestEqual("First array element", JsonObject.ReadInt("numbers[0]"), 10);
	TestEqual("Second array element", JsonObject.ReadInt("numbers[1]"), 20);
	TestEqual("Third array element", JsonObject.ReadInt("numbers[2]"), 30);
	
	// Test adding different types to arrays
	JsonObject.AddStringToArray("tags", "important");
	JsonObject.AddStringToArray("tags", "urgent");
	
	TestEqual("String array element 0", JsonObject.ReadString("tags[0]"), FString("important"));
	TestEqual("String array element 1", JsonObject.ReadString("tags[1]"), FString("urgent"));
	
	// Test adding booleans to arrays
	JsonObject.AddBoolToArray("flags", true);
	JsonObject.AddBoolToArray("flags", false);
	JsonObject.AddBoolToArray("flags", true);
	
	TestEqual("Bool array element 0", JsonObject.ReadBool("flags[0]"), true);
	TestEqual("Bool array element 1", JsonObject.ReadBool("flags[1]"), false);
	TestEqual("Bool array element 2", JsonObject.ReadBool("flags[2]"), true);
	
	// Test adding floats to arrays
	JsonObject.AddFloatToArray("measurements", 3.14f);
	JsonObject.AddFloatToArray("measurements", 2.71f);
	
	TestEqual("Float array element 0", JsonObject.ReadFloat("measurements[0]"), 3.14f);
	TestEqual("Float array element 1", JsonObject.ReadFloat("measurements[1]"), 2.71f);
	
	// Test adding objects to arrays
	FEasyJsonObjectV2 Item1 = FEasyJsonObjectV2::CreateEmpty();
	Item1.WriteString("name", "Item1");
	Item1.WriteInt("value", 100);
	
	FEasyJsonObjectV2 Item2 = FEasyJsonObjectV2::CreateEmpty();
	Item2.WriteString("name", "Item2");
	Item2.WriteInt("value", 200);
	
	JsonObject.AddObjectToArray("items", Item1);
	JsonObject.AddObjectToArray("items", Item2);
	
	TestEqual("Object array element name", JsonObject.ReadString("items[0].name"), FString("Item1"));
	TestEqual("Object array element value", JsonObject.ReadInt("items[0].value"), 100);
	TestEqual("Object array element name", JsonObject.ReadString("items[1].name"), FString("Item2"));
	TestEqual("Object array element value", JsonObject.ReadInt("items[1].value"), 200);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2ComplexWriteTest, "EasyJsonParser.V2.ComplexWrite", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2ComplexWriteTest::RunTest(const FString& Parameters)
{
	FEasyJsonObjectV2 JsonObject = FEasyJsonObjectV2::CreateEmpty();
	
	// Create complex nested structure
	JsonObject.WriteString("user.profile.name", "John Doe");
	JsonObject.WriteInt("user.profile.age", 30);
	JsonObject.WriteString("user.profile.email", "john@example.com");
	
	JsonObject.WriteString("user.settings.theme", "dark");
	JsonObject.WriteBool("user.settings.notifications.email", true);
	JsonObject.WriteBool("user.settings.notifications.sms", false);
	JsonObject.WriteInt("user.settings.privacy.level", 2);
	
	// Create array of nested objects
	JsonObject.WriteString("user.addresses[0].type", "home");
	JsonObject.WriteString("user.addresses[0].street", "123 Main St");
	JsonObject.WriteString("user.addresses[0].city", "Tokyo");
	
	JsonObject.WriteString("user.addresses[1].type", "work");
	JsonObject.WriteString("user.addresses[1].street", "456 Business Ave");
	JsonObject.WriteString("user.addresses[1].city", "Osaka");
	
	// Add skills array
	JsonObject.AddStringToArray("user.skills", "C++");
	JsonObject.AddStringToArray("user.skills", "Unreal Engine");
	JsonObject.AddStringToArray("user.skills", "Blueprint");
	
	// Verify complex structure
	TestEqual("Nested profile name", JsonObject.ReadString("user.profile.name"), FString("John Doe"));
	TestEqual("Nested profile age", JsonObject.ReadInt("user.profile.age"), 30);
	TestEqual("Nested email", JsonObject.ReadString("user.profile.email"), FString("john@example.com"));
	
	TestEqual("Nested theme", JsonObject.ReadString("user.settings.theme"), FString("dark"));
	TestEqual("Nested email notifications", JsonObject.ReadBool("user.settings.notifications.email"), true);
	TestEqual("Nested sms notifications", JsonObject.ReadBool("user.settings.notifications.sms"), false);
	TestEqual("Nested privacy level", JsonObject.ReadInt("user.settings.privacy.level"), 2);
	
	TestEqual("Address array type", JsonObject.ReadString("user.addresses[0].type"), FString("home"));
	TestEqual("Address array street", JsonObject.ReadString("user.addresses[0].street"), FString("123 Main St"));
	TestEqual("Address array city", JsonObject.ReadString("user.addresses[0].city"), FString("Tokyo"));
	
	TestEqual("Work address type", JsonObject.ReadString("user.addresses[1].type"), FString("work"));
	TestEqual("Work address street", JsonObject.ReadString("user.addresses[1].street"), FString("456 Business Ave"));
	TestEqual("Work address city", JsonObject.ReadString("user.addresses[1].city"), FString("Osaka"));
	
	TestEqual("Skills array element 0", JsonObject.ReadString("user.skills[0]"), FString("C++"));
	TestEqual("Skills array element 1", JsonObject.ReadString("user.skills[1]"), FString("Unreal Engine"));
	TestEqual("Skills array element 2", JsonObject.ReadString("user.skills[2]"), FString("Blueprint"));
	
	// Test JSON string output
	FString JsonString = JsonObject.ToString(false);
	TestTrue("JSON string should not be empty", !JsonString.IsEmpty());
	
	// Test round-trip
	bool bSuccess = false;
	FString ErrorMessage;
	FEasyJsonObjectV2 ReloadedObject = FEasyJsonObjectV2::CreateFromString(JsonString, bSuccess);
	
	TestTrue("Round-trip should succeed", bSuccess);
	TestEqual("Round-trip name should match", ReloadedObject.ReadString("user.profile.name"), FString("John Doe"));
	TestEqual("Round-trip skills should match", ReloadedObject.ReadString("user.skills[1]"), FString("Unreal Engine"));
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2FileWriteTest, "EasyJsonParser.V2.FileWrite", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2FileWriteTest::RunTest(const FString& Parameters)
{
	FEasyJsonObjectV2 JsonObject = FEasyJsonObjectV2::CreateEmpty();
	
	// Create test data
	JsonObject.WriteString("test.name", "FileWriteTest");
	JsonObject.WriteInt("test.value", 42);
	JsonObject.WriteBool("test.success", true);
	JsonObject.AddStringToArray("test.tags", "automation");
	JsonObject.AddStringToArray("test.tags", "testing");
	
	// Test save to file
	FString ErrorMessage;
	const FString TestFileName = "test_write_output.json";
	bool bSaveSuccess = UEasyJsonParseManagerV2::SaveToFile(JsonObject, TestFileName, false, ErrorMessage);
	
	TestTrue("Save to file should succeed", bSaveSuccess);
	if (!bSaveSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Save failed: %s"), *ErrorMessage);
	}
	
	// Test load from file
	bool bLoadSuccess = false;
	FEasyJsonObjectV2 LoadedObject = UEasyJsonParseManagerV2::LoadFromFile(TestFileName, false, bLoadSuccess, ErrorMessage);
	
	TestTrue("Load from file should succeed", bLoadSuccess);
	if (!bLoadSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Load failed: %s"), *ErrorMessage);
	}
	
	// Verify loaded data
	TestEqual("Loaded name should match", LoadedObject.ReadString("test.name"), FString("FileWriteTest"));
	TestEqual("Loaded value should match", LoadedObject.ReadInt("test.value"), 42);
	TestEqual("Loaded bool should match", LoadedObject.ReadBool("test.success"), true);
	TestEqual("Loaded array element should match", LoadedObject.ReadString("test.tags[0]"), FString("automation"));
	TestEqual("Loaded array element should match", LoadedObject.ReadString("test.tags[1]"), FString("testing"));
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2PathAutoCreationTest, "EasyJsonParser.V2.PathAutoCreation", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2PathAutoCreationTest::RunTest(const FString& Parameters)
{
	FEasyJsonObjectV2 JsonObject = FEasyJsonObjectV2::CreateEmpty();
	
	// Test 1: Auto-create simple nested path
	JsonObject.WriteString("settings.theme", "dark");
	TestEqual("Should auto-create path and set value", JsonObject.ReadString("settings.theme"), FString("dark"));
	
	// Verify intermediate object was created
	bool bFound = false;
	FEasyJsonObjectV2 SettingsObj = JsonObject.ReadObject("settings", bFound);
	TestTrue("Settings object should exist", bFound);
	TestTrue("Settings object should be valid", SettingsObj.IsValid());
	TestEqual("Should read theme from settings object", SettingsObj.ReadString("theme"), FString("dark"));
	
	// Test 2: Auto-create deep nested path
	JsonObject.WriteInt("user.preferences.display.brightness", 80);
	JsonObject.WriteBool("user.preferences.display.fullscreen", true);
	
	TestEqual("Should read nested brightness", JsonObject.ReadInt("user.preferences.display.brightness"), 80);
	TestEqual("Should read nested fullscreen", JsonObject.ReadBool("user.preferences.display.fullscreen"), true);
	
	// Verify all intermediate objects exist
	FEasyJsonObjectV2 UserObj = JsonObject.ReadObject("user", bFound);
	TestTrue("User object should exist", bFound);
	
	FEasyJsonObjectV2 PrefsObj = JsonObject.ReadObject("user.preferences", bFound);
	TestTrue("Preferences object should exist", bFound);
	
	FEasyJsonObjectV2 DisplayObj = JsonObject.ReadObject("user.preferences.display", bFound);
	TestTrue("Display object should exist", bFound);
	
	// Test 3: Auto-create array elements
	JsonObject.WriteString("profiles[0].name", "Default Profile");
	JsonObject.WriteInt("profiles[0].id", 1);
	JsonObject.WriteString("profiles[1].name", "Work Profile");
	JsonObject.WriteInt("profiles[1].id", 2);
	
	TestEqual("Array element 0 name", JsonObject.ReadString("profiles[0].name"), FString("Default Profile"));
	TestEqual("Array element 0 id", JsonObject.ReadInt("profiles[0].id"), 1);
	TestEqual("Array element 1 name", JsonObject.ReadString("profiles[1].name"), FString("Work Profile"));
	TestEqual("Array element 1 id", JsonObject.ReadInt("profiles[1].id"), 2);
	
	// Test 4: Complex nested array object creation
	JsonObject.WriteString("data.users[0].settings.language", "en");
	JsonObject.WriteBool("data.users[0].settings.notifications", true);
	JsonObject.WriteString("data.users[1].settings.language", "ja");
	JsonObject.WriteBool("data.users[1].settings.notifications", false);
	
	TestEqual("Complex nested language user 0", JsonObject.ReadString("data.users[0].settings.language"), FString("en"));
	TestEqual("Complex nested notifications user 0", JsonObject.ReadBool("data.users[0].settings.notifications"), true);
	TestEqual("Complex nested language user 1", JsonObject.ReadString("data.users[1].settings.language"), FString("ja"));
	TestEqual("Complex nested notifications user 1", JsonObject.ReadBool("data.users[1].settings.notifications"), false);
	
	// Test 5: Create intermediate path levels
	JsonObject.WriteString("level1.level2.level3.level4.deepValue", "success");
	
	// Verify all intermediate levels exist
	FEasyJsonObjectV2 Level1 = JsonObject.ReadObject("level1", bFound);
	TestTrue("Level1 should exist", bFound && Level1.IsValid());
	
	FEasyJsonObjectV2 Level2 = JsonObject.ReadObject("level1.level2", bFound);
	TestTrue("Level2 should exist", bFound && Level2.IsValid());
	
	FEasyJsonObjectV2 Level3 = JsonObject.ReadObject("level1.level2.level3", bFound);
	TestTrue("Level3 should exist", bFound && Level3.IsValid());
	
	FEasyJsonObjectV2 Level4 = JsonObject.ReadObject("level1.level2.level3.level4", bFound);
	TestTrue("Level4 should exist", bFound && Level4.IsValid());
	
	TestEqual("Deep value should be readable", JsonObject.ReadString("level1.level2.level3.level4.deepValue"), FString("success"));
	
	// Test 6: Mixed array and object creation
	JsonObject.WriteFloat("items[2].properties.advanced.weight", 2.5f);
	JsonObject.WriteString("items[2].properties.advanced.material", "steel");
	
	TestEqual("Mixed path weight", JsonObject.ReadFloat("items[2].properties.advanced.weight"), 2.5f);
	TestEqual("Mixed path material", JsonObject.ReadString("items[2].properties.advanced.material"), FString("steel"));
	
	// Test 7: Overwrite protection - should not lose existing data
	JsonObject.WriteString("existing.data", "important");
	JsonObject.WriteString("existing.newData", "additional");
	
	TestEqual("Should have original data", JsonObject.ReadString("existing.data"), FString("important"));
	TestEqual("Should have new data", JsonObject.ReadString("existing.newData"), FString("additional"));
	
	// Verify existing object structure
	FEasyJsonObjectV2 ExistingObj = JsonObject.ReadObject("existing", bFound);
	TestTrue("Existing object should be found", bFound);
	TestEqual("Should read data from existing object", ExistingObj.ReadString("data"), FString("important"));
	TestEqual("Should read newData from existing object", ExistingObj.ReadString("newData"), FString("additional"));
	
	// Test 8: Array of objects with mixed types
	JsonObject.WriteString("inventory[0].type", "weapon");
	JsonObject.WriteString("inventory[0].name", "Sword");
	JsonObject.WriteInt("inventory[0].damage", 50);
	JsonObject.WriteBool("inventory[0].equipped", true);
	
	JsonObject.WriteString("inventory[1].type", "armor");
	JsonObject.WriteString("inventory[1].name", "Shield");
	JsonObject.WriteInt("inventory[1].defense", 25);
	JsonObject.WriteBool("inventory[1].equipped", false);
	
	TestEqual("Inventory item 0 type", JsonObject.ReadString("inventory[0].type"), FString("weapon"));
	TestEqual("Inventory item 0 name", JsonObject.ReadString("inventory[0].name"), FString("Sword"));
	TestEqual("Inventory item 0 damage", JsonObject.ReadInt("inventory[0].damage"), 50);
	TestEqual("Inventory item 0 equipped", JsonObject.ReadBool("inventory[0].equipped"), true);
	
	TestEqual("Inventory item 1 type", JsonObject.ReadString("inventory[1].type"), FString("armor"));
	TestEqual("Inventory item 1 name", JsonObject.ReadString("inventory[1].name"), FString("Shield"));
	TestEqual("Inventory item 1 defense", JsonObject.ReadInt("inventory[1].defense"), 25);
	TestEqual("Inventory item 1 equipped", JsonObject.ReadBool("inventory[1].equipped"), false);
	
	// Test 9: Write to existing structure should not break it
	JsonObject.WriteString("user.profile.email", "user@example.com");
	
	// Verify existing user structure is intact
	TestEqual("Should still have brightness", JsonObject.ReadInt("user.preferences.display.brightness"), 80);
	TestEqual("Should still have fullscreen", JsonObject.ReadBool("user.preferences.display.fullscreen"), true);
	TestEqual("Should have new email", JsonObject.ReadString("user.profile.email"), FString("user@example.com"));
	
	// Test 10: JSON structure integrity
	FString JsonString = JsonObject.ToString(false);
	TestTrue("JSON string should not be empty", !JsonString.IsEmpty());
	
	// Test round-trip to ensure structure is valid
	bool bSuccess = false;
	FEasyJsonObjectV2 ReloadedObject = FEasyJsonObjectV2::CreateFromString(JsonString, bSuccess);
	TestTrue("Round-trip should succeed", bSuccess);
	
	// Verify some key values after round-trip
	TestEqual("Round-trip settings theme", ReloadedObject.ReadString("settings.theme"), FString("dark"));
	TestEqual("Round-trip deep value", ReloadedObject.ReadString("level1.level2.level3.level4.deepValue"), FString("success"));
	TestEqual("Round-trip array value", ReloadedObject.ReadString("profiles[0].name"), FString("Default Profile"));
	TestEqual("Round-trip mixed path", ReloadedObject.ReadFloat("items[2].properties.advanced.weight"), 2.5f);
	
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS