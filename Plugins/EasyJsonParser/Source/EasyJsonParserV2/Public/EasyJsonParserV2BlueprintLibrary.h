// Copyright 2025 ayumax. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasyJsonObjectV2.h"
#include "EasyJsonParserV2Enums.h"
#include "EasyJsonParserV2BlueprintLibrary.generated.h"

/**
 * Blueprint Function Library - Make all EasyJsonParserV2 functionality available from Blueprint
 */
UCLASS()
class EASYJSONPARSERV2_API UEasyJsonParserV2BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// ========================================
	// JSON loading functionality
	// ========================================
	
	/**
	 * Load JSON from file
	 * @param FilePath Path to the JSON file to load
	 * @param bAbsolutePath Whether to use absolute path
	 * @param bSuccess Success flag for loading
	 * @param ErrorMessage Error message
	 * @return Loaded JSON object
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Load", meta = (Keywords = "json load file"))
	static FEasyJsonObjectV2 LoadJsonFromFile(const FString& FilePath, bool bAbsolutePath, bool& bSuccess, FString& ErrorMessage);

	/**
	 * Load JSON from string
	 * @param JsonString JSON string
	 * @param bSuccess Success flag for loading
	 * @param ErrorMessage Error message
	 * @return Loaded JSON object
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Load", meta = (Keywords = "json load string"))
	static FEasyJsonObjectV2 LoadJsonFromString(const FString& JsonString, bool& bSuccess, FString& ErrorMessage);

	/**
	 * Create empty JSON object
	 * @return Empty JSON object
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Create", meta = (Keywords = "json create empty"))
	static FEasyJsonObjectV2 CreateEmptyJsonObject();

	// ========================================
	// JSON reading operations
	// ========================================

	/**
	 * Read integer value
	 * @param JsonObject JSON object
	 * @param AccessString Access string
	 * @param DefaultValue Default value
	 * @return Read integer value
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read int integer"))
	static int32 ReadInt(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, int32 DefaultValue = 0);

	/**
	 * Read floating point value
	 * @param JsonObject JSON object
	 * @param AccessString Access string
	 * @param DefaultValue Default value
	 * @return Read floating point value
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read float"))
	static float ReadFloat(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, float DefaultValue = 0.0f);

	/**
	 * Read string value
	 * @param JsonObject JSON object
	 * @param AccessString Access string
	 * @param DefaultValue Default value
	 * @return Read string value
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read string"))
	static FString ReadString(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FString& DefaultValue = TEXT(""));

	/**
	 * Read boolean value
	 * @param JsonObject JSON object
	 * @param AccessString Access string
	 * @param DefaultValue Default value
	 * @return Read boolean value
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read bool boolean"))
	static bool ReadBool(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, bool DefaultValue = false);

	/**
	 * Read object
	 * @param JsonObject JSON object
	 * @param AccessString Access string
	 * @return Read object
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read object"))
	static FEasyJsonObjectV2 ReadObject(const FEasyJsonObjectV2& JsonObject, const FString& AccessString);

	/**
	 * Read object array
	 * @param JsonObject JSON object
	 * @param AccessString Access string
	 * @return Read object array
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read objects array"))
	static TArray<FEasyJsonObjectV2> ReadObjects(const FEasyJsonObjectV2& JsonObject, const FString& AccessString);

	// ========================================
	// JSON writing operations
	// ========================================

	/**
	 * Write integer value
	 * @param JsonObject JSON object (passed by reference)
	 * @param AccessString Access string
	 * @param Value Value to write
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Write", meta = (Keywords = "json write int integer"))
	static void WriteInt(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, int32 Value);

	/**
	 * Write floating point value
	 * @param JsonObject JSON object (passed by reference)
	 * @param AccessString Access string
	 * @param Value Value to write
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Write", meta = (Keywords = "json write float"))
	static void WriteFloat(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, float Value);

	/**
	 * Write string value
	 * @param JsonObject JSON object (passed by reference)
	 * @param AccessString Access string
	 * @param Value Value to write
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Write", meta = (Keywords = "json write string"))
	static void WriteString(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FString& Value);

	/**
	 * Write boolean value
	 * @param JsonObject JSON object (passed by reference)
	 * @param AccessString Access string
	 * @param Value Value to write
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Write", meta = (Keywords = "json write bool boolean"))
	static void WriteBool(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, bool Value);

	/**
	 * Write object
	 * @param JsonObject JSON object (passed by reference)
	 * @param AccessString Access string
	 * @param Value Object to write
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Write", meta = (Keywords = "json write object"))
	static void WriteObject(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FEasyJsonObjectV2& Value);

	// ========================================
	// Array operations
	// ========================================

	/**
	 * Add integer value to array
	 * @param JsonObject JSON object (passed by reference)
	 * @param AccessString Access string
	 * @param Value Value to add
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Array", meta = (Keywords = "json array add int"))
	static void AddIntToArray(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, int32 Value);

	/**
	 * Add floating point value to array
	 * @param JsonObject JSON object (passed by reference)
	 * @param AccessString Access string
	 * @param Value Value to add
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Array", meta = (Keywords = "json array add float"))
	static void AddFloatToArray(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, float Value);

	/**
	 * Add string value to array
	 * @param JsonObject JSON object (passed by reference)
	 * @param AccessString Access string
	 * @param Value Value to add
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Array", meta = (Keywords = "json array add string"))
	static void AddStringToArray(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FString& Value);

	/**
	 * Add boolean value to array
	 * @param JsonObject JSON object (passed by reference)
	 * @param AccessString Access string
	 * @param Value Value to add
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Array", meta = (Keywords = "json array add bool"))
	static void AddBoolToArray(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, bool Value);

	/**
	 * Add object to array
	 * @param JsonObject JSON object (passed by reference)
	 * @param AccessString Access string
	 * @param Value Object to add
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Array", meta = (Keywords = "json array add object"))
	static void AddObjectToArray(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FEasyJsonObjectV2& Value);

	// ========================================
	// JSON saving functionality
	// ========================================

	/**
	 * Save JSON object to file
	 * @param JsonObject JSON object
	 * @param FilePath File path to save to
	 * @param bAbsolutePath Whether to use absolute path
	 * @param bPrettyPrint Whether to format for saving
	 * @param bSuccess Success flag for saving
	 * @param ErrorMessage Error message
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Save", meta = (Keywords = "json save file"))
	static void SaveJsonToFile(const FEasyJsonObjectV2& JsonObject, const FString& FilePath, bool bAbsolutePath, bool bPrettyPrint, bool& bSuccess, FString& ErrorMessage);

	/**
	 * Convert JSON object to string
	 * @param JsonObject JSON object
	 * @param bPrettyPrint Whether to format
	 * @return JSON string
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Convert", meta = (Keywords = "json to string"))
	static FString JsonToString(const FEasyJsonObjectV2& JsonObject, bool bPrettyPrint = true);

	// ========================================
	// Utility functionality
	// ========================================

	/**
	 * Check if JSON object is valid
	 * @param JsonObject JSON object
	 * @return true if valid
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Utility", meta = (Keywords = "json valid check"))
	static bool IsJsonObjectValid(const FEasyJsonObjectV2& JsonObject);

	/**
	 * Check if two JSON objects are equal
	 * @param JsonObjectA JSON object A to compare
	 * @param JsonObjectB JSON object B to compare
	 * @return true if equal
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Utility", meta = (Keywords = "json equal compare"))
	static bool AreJsonObjectsEqual(const FEasyJsonObjectV2& JsonObjectA, const FEasyJsonObjectV2& JsonObjectB);

	// ========================================
	// Debug functionality
	// ========================================

	/**
	 * Set debug mode
	 * @param bEnabled Whether to enable debug mode
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Debug", meta = (Keywords = "json debug mode"))
	static void SetDebugMode(bool bEnable);

	/**
	 * Get debug mode status
	 * @return true if debug mode is enabled
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Debug", meta = (Keywords = "json debug mode"))
	static bool IsDebugMode();

	/**
	 * Set debug log level
	 * @param LogLevel Log level to set
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Debug", meta = (Keywords = "json debug log level"))
	static void SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel InLogLevel);

	/**
	 * Get current debug log level
	 * @return Current log level
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Debug", meta = (Keywords = "json debug log level"))
	static EEasyJsonParserV2DebugLogLevel GetDebugLogLevel();
};