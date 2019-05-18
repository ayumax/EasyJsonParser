// Copyright 2019 ayumax. All Rights Reserved.
#include "Misc/AutomationTest.h"
#include "EasyJsonParseManager.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FReadValueTest_Int, "EasyJsonParser.ReadValueTest.Int", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FReadValueTest_Int::RunTest(const FString& Parameters)
{
	// parse success
	{
		/*FString xmlString = TEXT("<root>\r")
								TEXT("<!-- comment desu -->\r")
								TEXT("<abc attr1=\"10\" attr2=\"false\">\r")								
									TEXT("123\r")
								TEXT("</abc>\r")
							TEXT("</root>");

		EEasyJsonParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);
		
		TestEqual(TEXT("success read int"), rootNode->ReadInt(TEXT("root.abc"), 0), 123);*/
	}

	

	return true;
}
