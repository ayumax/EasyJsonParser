// Copyright 2019 ayumax. All Rights Reserved.
#include "Misc/AutomationTest.h"
#include "EasyJsonParseManager.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNodeAccessTest, "EasyJsonParser.NodeAccessTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FNodeAccessTest::RunTest(const FString& Parameters)
{
	{
		FString jsonString =
			TEXT("{")
				TEXT("\"glossary\":")
				TEXT("{")
					TEXT("\"title\": \"example glossary\",")
					TEXT("\"GlossDiv\" :")
					TEXT("{")
						TEXT("\"title\": \"S\",")
						TEXT("\"GlossList\" :")
						TEXT("{")
							TEXT("\"GlossEntry\":")
							TEXT("{")
								TEXT("\"ID\": \"SGML\",")
								TEXT("\"SortAs\" : \"SGML\",")
								TEXT("\"GlossTerm\" : \"Standard Generalized Markup Language\",")
								TEXT("\"Acronym\" : \"SGML\",")
								TEXT("\"Abbrev\" : \"ISO 8879:1986\",")
								TEXT("\"GlossDef\" :")
								TEXT("{")
									TEXT("\"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",")
									TEXT("\"GlossSeeAlso\" : [\"GML\", \"XML\"]")
								TEXT("},")
								TEXT("\"GlossSee\" : \"markup\"")
							TEXT("}")
						TEXT("}")
					TEXT("}")
				TEXT("}")
			TEXT("}");

		


		EEasyJsonParserErrorCode result;
		auto rootObject = UEasyJsonParseManager::LoadFromString(jsonString, result);
		
		TestEqual(TEXT("success load"), result, EEasyJsonParserErrorCode::Successed);
		
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.title")), TEXT("example glossary"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.GlossDiv.title")), TEXT("S"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.GlossDiv.GlossList.GlossEntry.ID")), TEXT("SGML"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.GlossDiv.GlossList.GlossEntry.SortAs")), TEXT("SGML"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.GlossDiv.GlossList.GlossEntry.GlossTerm")), TEXT("Standard Generalized Markup Language"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.GlossDiv.GlossList.GlossEntry.Acronym")), TEXT("SGML"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.GlossDiv.GlossList.GlossEntry.Abbrev")), TEXT("ISO 8879:1986"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.GlossDiv.GlossList.GlossEntry.GlossDef.para")), TEXT("A meta-markup language, used to create markup languages such as DocBook."));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.GlossDiv.GlossList.GlossEntry.GlossDef.GlossSeeAlso[0]")), TEXT("GML"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.GlossDiv.GlossList.GlossEntry.GlossDef.GlossSeeAlso[1]")), TEXT("XML"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("glossary.GlossDiv.GlossList.GlossEntry.GlossSee")), TEXT("markup"));

	}

	{
		FString jsonString =
			TEXT("{\"menu\":")
				TEXT("{")
					TEXT("\"id\": \"file\",")
					TEXT("\"value\" : \"File\",")
					TEXT("\"popup\" :")
					TEXT("{")
						TEXT("\"menuitem\":")
						TEXT("[")
						TEXT("{\"value\": \"New\", \"onclick\" : \"CreateNewDoc()\"},")
						TEXT("{ \"value\": \"Open\", \"onclick\" : \"OpenDoc()\" },")
						TEXT("{ \"value\": \"Close\", \"onclick\" : \"CloseDoc()\" }")
						TEXT("]")
					TEXT("}")
				TEXT("}")
			TEXT("}");

		EEasyJsonParserErrorCode result;
		auto rootObject = UEasyJsonParseManager::LoadFromString(jsonString, result);

		TestEqual(TEXT("success load"), result, EEasyJsonParserErrorCode::Successed);

		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.id")), TEXT("file"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.value")), TEXT("File"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.popup.menuitem[0].value")), TEXT("New"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.popup.menuitem[0].onclick")), TEXT("CreateNewDoc()"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.popup.menuitem[1].value")), TEXT("Open"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.popup.menuitem[1].onclick")), TEXT("OpenDoc()"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.popup.menuitem[2].value")), TEXT("Close"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.popup.menuitem[2].onclick")), TEXT("CloseDoc()"));
	}

	{
		FString jsonString =
				TEXT("{")
					TEXT("\"widget\":")
					TEXT("{")
						TEXT("\"debug\": \"on\",")
						TEXT("\"window\" : {")
							TEXT("\"title\": \"Sample Konfabulator Widget\",")
							TEXT("\"name\" : \"main_window\",")
							TEXT("\"width\" : 500,")
							TEXT("\"height\" : 500")
						TEXT("},")
						TEXT("\"image\": ")
						TEXT("{")
							TEXT("\"src\": \"Images/Sun.png\",")
							TEXT("\"name\" : \"sun1\",")
							TEXT("\"hOffset\" : 250,")
							TEXT("\"vOffset\" : 250,")
							TEXT("\"alignment\" : \"center\"")
						TEXT("},")
						TEXT("\"text\":")
						TEXT("{")
							TEXT("\"data\": \"Click Here\",")
							TEXT("\"size\" : 36,")
							TEXT("\"style\" : \"bold\",")
							TEXT("\"name\" : \"text1\",")
							TEXT("\"hOffset\" : 250,")
							TEXT("\"vOffset\" : 100,")
							TEXT("\"alignment\" : \"center\",")
							TEXT("\"onMouseUp\" : \"sun1.opacity = (sun1.opacity / 100) * 90;\"")
						TEXT("}")
					TEXT("} ")
				TEXT("}");

		EEasyJsonParserErrorCode result;
		auto rootObject = UEasyJsonParseManager::LoadFromString(jsonString, result);

		TestEqual(TEXT("success load"), result, EEasyJsonParserErrorCode::Successed);
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.debug")), TEXT("on"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.window.title")), TEXT("Sample Konfabulator Widget"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.window.name")), TEXT("main_window"));
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("widget.window.width")), 500);
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("widget.window.height")), 500);
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.image.src")), TEXT("Images/Sun.png"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.image.name")), TEXT("sun1"));
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("widget.image.hOffset")), 250);
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("widget.image.vOffset")), 250);
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.image.alignment")), TEXT("center"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.text.data")), TEXT("Click Here"));
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("widget.text.size")), 36);
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.text.style")), TEXT("bold"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.text.name")), TEXT("text1"));
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("widget.text.hOffset")), 250);
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("widget.text.vOffset")), 100);
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.text.alignment")), TEXT("center"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("widget.text.onMouseUp")), TEXT("sun1.opacity = (sun1.opacity / 100) * 90;"));
	}

	{
		FString jsonString =
			TEXT("{\"menu\": {")
				TEXT("\"header\": \"SVG Viewer\",")
				TEXT("\"items\" : [")
					TEXT("{\"id\": \"Open\"},")
					TEXT("{ \"id\": \"OpenNew\", \"label\" : \"Open New\" },")
					TEXT("null,")
					TEXT("{ \"id\": \"ZoomIn\", \"label\" : \"Zoom In\" },")
					TEXT("{ \"id\": \"ZoomOut\", \"label\" : \"Zoom Out\" },")
					TEXT("{ \"id\": \"OriginalView\", \"label\" : \"Original View\" },")
					TEXT("null,")
					TEXT("{ \"id\": \"Quality\" },")
					TEXT("{ \"id\": \"Pause\" },")
					TEXT("{ \"id\": \"Mute\" },")
					TEXT("null,")
					TEXT("{ \"id\": \"Find\", \"label\" : \"Find...\" },")
					TEXT("{ \"id\": \"FindAgain\", \"label\" : \"Find Again\" },")
					TEXT("{ \"id\": \"Copy\" },")
					TEXT("{ \"id\": \"CopyAgain\", \"label\" : \"Copy Again\" },")
					TEXT("{ \"id\": \"CopySVG\", \"label\" : \"Copy SVG\" },")
					TEXT("{ \"id\": \"ViewSVG\", \"label\" : \"View SVG\" },")
					TEXT("{ \"id\": \"ViewSource\", \"label\" : \"View Source\" },")
					TEXT("{ \"id\": \"SaveAs\", \"label\" : \"Save As\" },")
					TEXT("null,")
					TEXT("{ \"id\": \"Help\" },")
					TEXT("{ \"id\": \"About\", \"label\" : \"About Adobe CVG Viewer...\" }")
				TEXT("]")
			TEXT("}}");

		EEasyJsonParserErrorCode result;
		auto rootObject = UEasyJsonParseManager::LoadFromString(jsonString, result);

		TestEqual(TEXT("success load"), result, EEasyJsonParserErrorCode::Successed);
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.header")), TEXT("SVG Viewer"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[0].id")), TEXT("Open"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[1].id")), TEXT("OpenNew"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[1].label")), TEXT("Open New"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[3].id")), TEXT("ZoomIn"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[3].label")), TEXT("Zoom In"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[4].id")), TEXT("ZoomOut"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[4].label")), TEXT("Zoom Out"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[5].id")), TEXT("OriginalView"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[5].label")), TEXT("Original View"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[7].id")), TEXT("Quality"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[8].id")), TEXT("Pause"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[9].id")), TEXT("Mute"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[11].id")), TEXT("Find"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[11].label")), TEXT("Find..."));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[12].id")), TEXT("FindAgain"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[12].label")), TEXT("Find Again"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[13].id")), TEXT("Copy"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[14].id")), TEXT("CopyAgain"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[14].label")), TEXT("Copy Again"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[15].id")), TEXT("CopySVG"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[15].label")), TEXT("Copy SVG"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[16].id")), TEXT("ViewSVG"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[16].label")), TEXT("View SVG"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[17].id")), TEXT("ViewSource"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[17].label")), TEXT("View Source"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[18].id")), TEXT("SaveAs"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[18].label")), TEXT("Save As"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[20].id")), TEXT("Help"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[21].id")), TEXT("About"));
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("menu.items[21].label")), TEXT("About Adobe CVG Viewer..."));
	}

	{
		FString jsonString =
			TEXT("[")
				TEXT("{\"index\":1},")
				TEXT("{\"index\":2},")
				TEXT("{\"index\":3}")
			TEXT("]");

		EEasyJsonParserErrorCode result;
		auto rootObject = UEasyJsonParseManager::LoadFromString(jsonString, result);

		TestEqual(TEXT("success load"), result, EEasyJsonParserErrorCode::Successed);
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("root[0].index")), 1);
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("root[1].index")), 2);
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("root[2].index")), 3);
	}

	{
		FString jsonString =
			TEXT("[")
			TEXT("{\"index\":1},")
			TEXT("{\"index\":2},")
			TEXT("{\"index\":3}")
			TEXT("]");

		EEasyJsonParserErrorCode result;
		auto rootObject = UEasyJsonParseManager::LoadFromString(jsonString, result);

		EEasyJsonParserFound result2;
		auto arrays = rootObject->ReadObjects("root", result2);
		TestEqual(TEXT("success read"), arrays.Num(), 3);
		TestEqual(TEXT("success read"), arrays[0]->ReadInt(TEXT("index")), 1);
		TestEqual(TEXT("success read"), arrays[1]->ReadInt(TEXT("index")), 2);
		TestEqual(TEXT("success read"), arrays[2]->ReadInt(TEXT("index")), 3);
	}

	{
		FString jsonString =
			TEXT("[")
			TEXT("1,")
			TEXT("\"abc\",")
			TEXT("3.14,")
			TEXT("true")
			TEXT("]");

		EEasyJsonParserErrorCode result;
		auto rootObject = UEasyJsonParseManager::LoadFromString(jsonString, result);

		TestEqual(TEXT("success load"), result, EEasyJsonParserErrorCode::Successed);
		TestEqual(TEXT("success read"), rootObject->ReadInt(TEXT("root[0]")), 1);
		TestEqual(TEXT("success read"), rootObject->ReadString(TEXT("root[1]")), TEXT("abc"));
		TestEqual(TEXT("success read"), rootObject->ReadFloat(TEXT("root[2]")), 3.14f);
		TestEqual(TEXT("success read"), rootObject->ReadBool(TEXT("root[3]")), true);
	}

	{
		FString jsonString =
			TEXT("{\"menu\":")
				TEXT("{")
					TEXT("\"id\": \"file\",")
					TEXT("\"value\" : \"File\",")
					TEXT("\"popup\" :")
					TEXT("{")
					TEXT("\"menuitem\":")
					TEXT("[")
						TEXT("{\"value\": \"New\", \"onclick\" : \"CreateNewDoc()\"},")
						TEXT("{ \"value\": \"Open\", \"onclick\" : \"OpenDoc()\" },")
						TEXT("{ \"value\": \"Close\", \"onclick\" : \"CloseDoc()\" }")
					TEXT("]")
					TEXT("}")
				TEXT("}");

		EEasyJsonParserErrorCode result;
		auto rootObject = UEasyJsonParseManager::LoadFromString(jsonString, result);

		TestEqual(TEXT("failed load"), result, EEasyJsonParserErrorCode::Failed);

	}

	{
		FString jsonString =
			TEXT("\"menu\":")
			TEXT("{")
				TEXT("\"id\": \"file\",")
				TEXT("\"value\" : \"File\",")
				TEXT("\"popup\" :")
				TEXT("{")
				TEXT("\"menuitem\":")
				TEXT("[")
					TEXT("{\"value\": \"New\", \"onclick\" : \"CreateNewDoc()\"},")
					TEXT("{ \"value\": \"Open\", \"onclick\" : \"OpenDoc()\" },")
					TEXT("{ \"value\": \"Close\", \"onclick\" : \"CloseDoc()\" }")
				TEXT("]")
				TEXT("}")
			TEXT("}")
		TEXT("}");

		EEasyJsonParserErrorCode result;
		auto rootObject = UEasyJsonParseManager::LoadFromString(jsonString, result);

		TestEqual(TEXT("failed load"), result, EEasyJsonParserErrorCode::Failed);

	}

	{
		FString jsonString =
			TEXT("{\"menu\":")
				TEXT("{")
					TEXT("\"id\": \"file\",")
					TEXT("\"value\" : \"File\",")
					TEXT("\"popup\" :")
					TEXT("{")
						TEXT("\"menuitem\":")
						TEXT("[")
							TEXT("{\"value\": \"New\", \"onclick\" : \"CreateNewDoc()\"},")
							TEXT("{ \"value\": \"Open\", \"onclick\" : \"OpenDoc()\" },")
							TEXT("{ \"value\": \"Close\", \"onclick\" : \"CloseDoc()\" }")
						TEXT("]")
					TEXT("}")
				TEXT("}")
			TEXT("}");

		EEasyJsonParserErrorCode result;
		auto rootObject = UEasyJsonParseManager::LoadFromString(jsonString, result);

		TestEqual(TEXT("success load"), result, EEasyJsonParserErrorCode::Successed);

		TestEqual(TEXT("failed read"), rootObject->ReadString(TEXT("menu")), TEXT(""));
		TestEqual(TEXT("failed read"), rootObject->ReadString(TEXT("menu[1]")), TEXT(""));
		TestEqual(TEXT("failed read"), rootObject->ReadString(TEXT("menu.name")), TEXT(""));
		TestEqual(TEXT("failed read"), rootObject->ReadString(TEXT("menu.menuitem")), TEXT(""));
		TestEqual(TEXT("failed read"), rootObject->ReadString(TEXT("menu.menuitem[3].value")), TEXT(""));

	}

	return true;
}

