// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Engine/Engine.h"
#include "EasyJsonObjectV2.h"
#include "EasyJsonParseManagerV2.h"
#include "AdvancedAccessParser.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEasyJsonParserV2AdvancedArrayTest, "EasyJsonParser.V2.AdvancedArray", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FEasyJsonParserV2AdvancedArrayTest::RunTest(const FString& Parameters)
{
	// Create test JSON with nested arrays
	const FString TestJson = TEXT(R"({
		"matrix": [
			[1, 2, 3],
			[4, 5, 6],
			[7, 8, 9]
		],
		"cube": [
			[
				[1, 2], [3, 4]
			],
			[
				[5, 6], [7, 8]
			]
		],
		"users": [
			{
				"name": "Alice",
				"contacts": [
					{
						"type": "email",
						"values": ["alice@work.com", "alice@home.com"]
					},
					{
						"type": "phone", 
						"values": ["123-456-7890"]
					}
				]
			},
			{
				"name": "Bob",
				"contacts": [
					{
						"type": "email",
						"values": ["bob@work.com"]
					}
				]
			}
		],
		"mixed_data": [
			[1, 2],
			"string",
			{"nested": "object"},
			[3, 4, 5]
		]
	})");
	
	// Test loading
	bool bSuccess = false;
	FString ErrorMessage;
	FEasyJsonObjectV2 JsonObject = UEasyJsonParseManagerV2::LoadFromString(TestJson, bSuccess, ErrorMessage);
	
	TestTrue("JSON should load successfully", bSuccess);
	TestTrue("JSON object should be valid", JsonObject.IsValid());
	
	// Test 2D array access with dot notation
	TestEqual("Read 2D array element [0][1]", JsonObject.ReadInt("matrix[0][1]"), 2);
	TestEqual("Read 2D array element [1][2]", JsonObject.ReadInt("matrix[1][2]"), 6);
	TestEqual("Read 2D array element [2][0]", JsonObject.ReadInt("matrix[2][0]"), 7);
	
	// Test 2D array access with dedicated methods
	TestEqual("Read 2D array using method (0,1)", JsonObject.Read2DArrayInt("matrix", 0, 1), 2);
	TestEqual("Read 2D array using method (1,2)", JsonObject.Read2DArrayInt("matrix", 1, 2), 6);
	TestEqual("Read 2D array using method (2,0)", JsonObject.Read2DArrayInt("matrix", 2, 0), 7);
	
	// Test 3D array access
	TestEqual("Read 3D array element [0][0][1]", JsonObject.ReadInt("cube[0][0][1]"), 2);
	TestEqual("Read 3D array element [1][1][0]", JsonObject.ReadInt("cube[1][1][0]"), 7);
	
	// Test 3D array access with dedicated methods
	TestEqual("Read 3D array using method (0,0,1)", JsonObject.Read3DArrayInt("cube", 0, 0, 1), 2);
	TestEqual("Read 3D array using method (1,1,0)", JsonObject.Read3DArrayInt("cube", 1, 1, 0), 7);
	
	// Test complex nested access
	TestEqual("Read nested array in object", JsonObject.ReadString("users[0].contacts[0].values[1]"), FString("alice@home.com"));
	TestEqual("Read nested array in object", JsonObject.ReadString("users[1].contacts[0].values[0]"), FString("bob@work.com"));
	
	// Test array utility methods
	TestEqual("Get array size - matrix", JsonObject.GetArraySize("matrix"), 3);
	TestEqual("Get array size - nested", JsonObject.GetArraySize("matrix[0]"), 3);
	TestEqual("Get array size - deep nested", JsonObject.GetArraySize("users[0].contacts[0].values"), 2);
	
	// Test array type checking
	TestTrue("matrix should be an array", JsonObject.IsArray("matrix"));
	TestTrue("matrix[0] should be an array", JsonObject.IsArray("matrix[0]"));
	TestFalse("matrix[0][0] should not be an array", JsonObject.IsArray("matrix[0][0]"));
	
	// Test array dimensions
	TestEqual("matrix dimensions", JsonObject.GetArrayDimensions("matrix[0][0]"), 2);
	TestEqual("cube dimensions", JsonObject.GetArrayDimensions("cube[0][0][0]"), 3);
	
	// Test array dimension sizes
	TArray<int32> MatrixDimensions = JsonObject.GetArrayDimensionSizes("matrix");
	TestEqual("Matrix dimension count", MatrixDimensions.Num(), 2);
	if (MatrixDimensions.Num() >= 2)
	{
		TestEqual("Matrix first dimension", MatrixDimensions[0], 3);
		TestEqual("Matrix second dimension", MatrixDimensions[1], 3);
	}
	
	// Test safe array access
	FEasyJsonValueV2 SafeElement = JsonObject.SafeReadArrayElement("matrix", 1);
	TestTrue("Safe array access should return valid element", SafeElement.IsValid());
	TestTrue("Safe array access element should be array", SafeElement.IsArray());
	
	// Test safe array access out of bounds
	FEasyJsonValueV2 OutOfBounds = JsonObject.SafeReadArrayElement("matrix", 10);
	TestFalse("Out of bounds access should return invalid element", OutOfBounds.IsValid());
	
	// Test read all array values
	TArray<FEasyJsonValueV2> MatrixRow = JsonObject.ReadArrayValues("matrix[0]");
	TestEqual("Matrix row should have 3 elements", MatrixRow.Num(), 3);
	if (MatrixRow.Num() >= 3)
	{
		TestEqual("First element should be 1", MatrixRow[0].GetIntValue(), 1);
		TestEqual("Second element should be 2", MatrixRow[1].GetIntValue(), 2);
		TestEqual("Third element should be 3", MatrixRow[2].GetIntValue(), 3);
	}
	
	// Test multi-dimensional array access
	TArray<int32> Indices = {1, 0, 1};
	FEasyJsonValueV2 MultiDimResult = JsonObject.ReadMultiDimensionalArray("cube", Indices);
	TestTrue("Multi-dimensional access should return valid result", MultiDimResult.IsValid());
	TestEqual("Multi-dimensional access result", MultiDimResult.GetIntValue(), 6);
	
	// Test mixed array access
	TestEqual("Mixed array int element", JsonObject.ReadInt("mixed_data[0][0]"), 1);
	TestEqual("Mixed array string element", JsonObject.ReadString("mixed_data[1]"), FString("string"));
	TestEqual("Mixed array object element", JsonObject.ReadString("mixed_data[2].nested"), FString("object"));
	TestEqual("Mixed array nested array", JsonObject.ReadInt("mixed_data[3][2]"), 5);
	
	// Test error cases with default values
	TestEqual("Non-existent path should return default", JsonObject.ReadInt("nonexistent[0][0]", 999), 999);
	TestEqual("Out of bounds should return default", JsonObject.ReadInt("matrix[10][10]", 999), 999);
	TestEqual("Wrong type access should return default", JsonObject.ReadInt("users[0].name[0]", 999), 999);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAdvancedAccessParserTest, "EasyJsonParser.V2.AdvancedAccessParser", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAdvancedAccessParserTest::RunTest(const FString& Parameters)
{
	// Test basic parsing
	TArray<FAccessStep> BasicSteps = FAdvancedAccessParser::ParseAccessString("property");
	TestEqual("Basic property parse", BasicSteps.Num(), 1);
	if (BasicSteps.Num() > 0)
	{
		TestEqual("Basic property name", BasicSteps[0].PropertyName, FString("property"));
		TestFalse("Basic property should not be array access", BasicSteps[0].bIsArrayAccess);
	}
	
	// Test simple array parsing
	TArray<FAccessStep> ArraySteps = FAdvancedAccessParser::ParseAccessString("array[0]");
	TestEqual("Simple array parse", ArraySteps.Num(), 1);
	if (ArraySteps.Num() > 0)
	{
		TestEqual("Array property name", ArraySteps[0].PropertyName, FString("array"));
		TestTrue("Array property should be array access", ArraySteps[0].bIsArrayAccess);
		TestEqual("Array indices count", ArraySteps[0].ArrayIndices.Num(), 1);
		if (ArraySteps[0].ArrayIndices.Num() > 0)
		{
			TestEqual("Array index value", ArraySteps[0].ArrayIndices[0], 0);
		}
	}
	
	// Test nested array parsing
	TArray<FAccessStep> NestedSteps = FAdvancedAccessParser::ParseAccessString("matrix[1][2]");
	TestEqual("Nested array parse", NestedSteps.Num(), 1);
	if (NestedSteps.Num() > 0)
	{
		TestEqual("Nested array property name", NestedSteps[0].PropertyName, FString("matrix"));
		TestTrue("Nested array should be array access", NestedSteps[0].bIsArrayAccess);
		TestEqual("Nested array indices count", NestedSteps[0].ArrayIndices.Num(), 2);
		if (NestedSteps[0].ArrayIndices.Num() >= 2)
		{
			TestEqual("First nested index", NestedSteps[0].ArrayIndices[0], 1);
			TestEqual("Second nested index", NestedSteps[0].ArrayIndices[1], 2);
		}
	}
	
	// Test complex parsing
	TArray<FAccessStep> ComplexSteps = FAdvancedAccessParser::ParseAccessString("users[0].contacts[1].values[0]");
	TestEqual("Complex parse step count", ComplexSteps.Num(), 3);
	if (ComplexSteps.Num() >= 3)
	{
		// First step: users[0]
		TestEqual("First step property", ComplexSteps[0].PropertyName, FString("users"));
		TestTrue("First step is array access", ComplexSteps[0].bIsArrayAccess);
		TestEqual("First step index", ComplexSteps[0].ArrayIndices[0], 0);
		
		// Second step: contacts[1]
		TestEqual("Second step property", ComplexSteps[1].PropertyName, FString("contacts"));
		TestTrue("Second step is array access", ComplexSteps[1].bIsArrayAccess);
		TestEqual("Second step index", ComplexSteps[1].ArrayIndices[0], 1);
		
		// Third step: values[0]
		TestEqual("Third step property", ComplexSteps[2].PropertyName, FString("values"));
		TestTrue("Third step is array access", ComplexSteps[2].bIsArrayAccess);
		TestEqual("Third step index", ComplexSteps[2].ArrayIndices[0], 0);
	}
	
	// Test validation
	TestTrue("Valid simple string", FAdvancedAccessParser::IsValidAccessString("property"));
	TestTrue("Valid array string", FAdvancedAccessParser::IsValidAccessString("array[0]"));
	TestTrue("Valid nested string", FAdvancedAccessParser::IsValidAccessString("a.b.c"));
	TestTrue("Valid complex string", FAdvancedAccessParser::IsValidAccessString("users[0].data[1][2]"));
	
	TestFalse("Invalid empty string", FAdvancedAccessParser::IsValidAccessString(""));
	TestFalse("Invalid leading dot", FAdvancedAccessParser::IsValidAccessString(".property"));
	TestFalse("Invalid trailing dot", FAdvancedAccessParser::IsValidAccessString("property."));
	TestFalse("Invalid double dot", FAdvancedAccessParser::IsValidAccessString("a..b"));
	TestFalse("Invalid bracket", FAdvancedAccessParser::IsValidAccessString("array["));
	TestFalse("Invalid bracket", FAdvancedAccessParser::IsValidAccessString("array]"));
	TestFalse("Invalid bracket content", FAdvancedAccessParser::IsValidAccessString("array[abc]"));
	
	// Test array access detection
	TestTrue("Should detect array access", FAdvancedAccessParser::ContainsArrayAccess("array[0]"));
	TestTrue("Should detect nested array access", FAdvancedAccessParser::ContainsArrayAccess("matrix[0][1]"));
	TestFalse("Should not detect array access", FAdvancedAccessParser::ContainsArrayAccess("property"));
	TestFalse("Should not detect array access", FAdvancedAccessParser::ContainsArrayAccess("a.b.c"));
	
	// Test max depth calculation
	TestEqual("No array depth", FAdvancedAccessParser::GetMaxArrayDepth("property"), 0);
	TestEqual("Single array depth", FAdvancedAccessParser::GetMaxArrayDepth("array[0]"), 1);
	TestEqual("Double array depth", FAdvancedAccessParser::GetMaxArrayDepth("matrix[0][1]"), 2);
	TestEqual("Triple array depth", FAdvancedAccessParser::GetMaxArrayDepth("cube[0][1][2]"), 3);
	TestEqual("Mixed depth", FAdvancedAccessParser::GetMaxArrayDepth("users[0].matrix[1][2]"), 2);
	
	// Test sanitization
	TestEqual("Sanitize spaces", FAdvancedAccessParser::SanitizeAccessString(" a . b "), FString("a.b"));
	TestEqual("Sanitize bracket spaces", FAdvancedAccessParser::SanitizeAccessString("array[ 0 ]"), FString("array[0]"));
	TestEqual("Sanitize mixed spaces", FAdvancedAccessParser::SanitizeAccessString(" a[ 0 ] . b [ 1 ] "), FString("a[0].b[1]"));
	
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS