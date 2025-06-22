// Copyright 2025 ayumax. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasyJsonObjectV2.h"
#include "EasyJsonParserV2Enums.h"
#include "EasyJsonParserV2BlueprintLibrary.generated.h"

/**
 * Blueprint関数ライブラリ - EasyJsonParserV2の全機能をBlueprintから使用可能にする
 */
UCLASS()
class EASYJSONPARSERV2_API UEasyJsonParserV2BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// ========================================
	// JSON読み込み機能
	// ========================================
	
	/**
	 * ファイルからJSONを読み込む
	 * @param FilePath 読み込むJSONファイルのパス
	 * @param bAbsolutePath 絶対パスを使用するかどうか
	 * @param bSuccess 読み込み成功フラグ
	 * @param ErrorMessage エラーメッセージ
	 * @return 読み込まれたJSONオブジェクト
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Load", meta = (Keywords = "json load file"))
	static FEasyJsonObjectV2 LoadJsonFromFile(const FString& FilePath, bool bAbsolutePath, bool& bSuccess, FString& ErrorMessage);

	/**
	 * 文字列からJSONを読み込む
	 * @param JsonString JSON文字列
	 * @param bSuccess 読み込み成功フラグ
	 * @param ErrorMessage エラーメッセージ
	 * @return 読み込まれたJSONオブジェクト
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Load", meta = (Keywords = "json load string"))
	static FEasyJsonObjectV2 LoadJsonFromString(const FString& JsonString, bool& bSuccess, FString& ErrorMessage);

	/**
	 * 空のJSONオブジェクトを作成する
	 * @return 空のJSONオブジェクト
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Create", meta = (Keywords = "json create empty"))
	static FEasyJsonObjectV2 CreateEmptyJsonObject();

	// ========================================
	// JSON読み込み操作
	// ========================================

	/**
	 * 整数値を読み込む
	 * @param JsonObject JSONオブジェクト
	 * @param AccessString アクセス文字列
	 * @param DefaultValue デフォルト値
	 * @return 読み込まれた整数値
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read int integer"))
	static int32 ReadInt(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, int32 DefaultValue = 0);

	/**
	 * 浮動小数点数値を読み込む
	 * @param JsonObject JSONオブジェクト
	 * @param AccessString アクセス文字列
	 * @param DefaultValue デフォルト値
	 * @return 読み込まれた浮動小数点数値
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read float"))
	static float ReadFloat(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, float DefaultValue = 0.0f);

	/**
	 * 文字列を読み込む
	 * @param JsonObject JSONオブジェクト
	 * @param AccessString アクセス文字列
	 * @param DefaultValue デフォルト値
	 * @return 読み込まれた文字列
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read string"))
	static FString ReadString(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FString& DefaultValue = TEXT(""));

	/**
	 * ブール値を読み込む
	 * @param JsonObject JSONオブジェクト
	 * @param AccessString アクセス文字列
	 * @param DefaultValue デフォルト値
	 * @return 読み込まれたブール値
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read bool boolean"))
	static bool ReadBool(const FEasyJsonObjectV2& JsonObject, const FString& AccessString, bool DefaultValue = false);

	/**
	 * オブジェクトを読み込む
	 * @param JsonObject JSONオブジェクト
	 * @param AccessString アクセス文字列
	 * @return 読み込まれたオブジェクト
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read object"))
	static FEasyJsonObjectV2 ReadObject(const FEasyJsonObjectV2& JsonObject, const FString& AccessString);

	/**
	 * オブジェクト配列を読み込む
	 * @param JsonObject JSONオブジェクト
	 * @param AccessString アクセス文字列
	 * @return 読み込まれたオブジェクト配列
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Read", meta = (Keywords = "json read objects array"))
	static TArray<FEasyJsonObjectV2> ReadObjects(const FEasyJsonObjectV2& JsonObject, const FString& AccessString);

	// ========================================
	// JSON書き込み操作
	// ========================================

	/**
	 * 整数値を書き込む
	 * @param JsonObject JSONオブジェクト（参照渡し）
	 * @param AccessString アクセス文字列
	 * @param Value 書き込む値
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Write", meta = (Keywords = "json write int integer"))
	static void WriteInt(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, int32 Value);

	/**
	 * 浮動小数点数値を書き込む
	 * @param JsonObject JSONオブジェクト（参照渡し）
	 * @param AccessString アクセス文字列
	 * @param Value 書き込む値
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Write", meta = (Keywords = "json write float"))
	static void WriteFloat(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, float Value);

	/**
	 * 文字列を書き込む
	 * @param JsonObject JSONオブジェクト（参照渡し）
	 * @param AccessString アクセス文字列
	 * @param Value 書き込む値
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Write", meta = (Keywords = "json write string"))
	static void WriteString(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FString& Value);

	/**
	 * ブール値を書き込む
	 * @param JsonObject JSONオブジェクト（参照渡し）
	 * @param AccessString アクセス文字列
	 * @param Value 書き込む値
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Write", meta = (Keywords = "json write bool boolean"))
	static void WriteBool(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, bool Value);

	/**
	 * オブジェクトを書き込む
	 * @param JsonObject JSONオブジェクト（参照渡し）
	 * @param AccessString アクセス文字列
	 * @param Value 書き込むオブジェクト
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Write", meta = (Keywords = "json write object"))
	static void WriteObject(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FEasyJsonObjectV2& Value);

	// ========================================
	// 配列操作
	// ========================================

	/**
	 * 配列に整数値を追加
	 * @param JsonObject JSONオブジェクト（参照渡し）
	 * @param AccessString アクセス文字列
	 * @param Value 追加する値
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Array", meta = (Keywords = "json array add int"))
	static void AddIntToArray(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, int32 Value);

	/**
	 * 配列に浮動小数点数値を追加
	 * @param JsonObject JSONオブジェクト（参照渡し）
	 * @param AccessString アクセス文字列
	 * @param Value 追加する値
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Array", meta = (Keywords = "json array add float"))
	static void AddFloatToArray(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, float Value);

	/**
	 * 配列に文字列を追加
	 * @param JsonObject JSONオブジェクト（参照渡し）
	 * @param AccessString アクセス文字列
	 * @param Value 追加する値
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Array", meta = (Keywords = "json array add string"))
	static void AddStringToArray(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FString& Value);

	/**
	 * 配列にブール値を追加
	 * @param JsonObject JSONオブジェクト（参照渡し）
	 * @param AccessString アクセス文字列
	 * @param Value 追加する値
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Array", meta = (Keywords = "json array add bool"))
	static void AddBoolToArray(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, bool Value);

	/**
	 * 配列にオブジェクトを追加
	 * @param JsonObject JSONオブジェクト（参照渡し）
	 * @param AccessString アクセス文字列
	 * @param Value 追加するオブジェクト
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Array", meta = (Keywords = "json array add object"))
	static void AddObjectToArray(UPARAM(ref) FEasyJsonObjectV2& JsonObject, const FString& AccessString, const FEasyJsonObjectV2& Value);

	// ========================================
	// JSON保存機能
	// ========================================

	/**
	 * JSONオブジェクトをファイルに保存
	 * @param JsonObject JSONオブジェクト
	 * @param FilePath 保存先ファイルパス
	 * @param bAbsolutePath 絶対パスを使用するかどうか
	 * @param bPrettyPrint 整形して保存するかどうか
	 * @param bSuccess 保存成功フラグ
	 * @param ErrorMessage エラーメッセージ
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Save", meta = (Keywords = "json save file"))
	static void SaveJsonToFile(const FEasyJsonObjectV2& JsonObject, const FString& FilePath, bool bAbsolutePath, bool bPrettyPrint, bool& bSuccess, FString& ErrorMessage);

	/**
	 * JSONオブジェクトを文字列に変換
	 * @param JsonObject JSONオブジェクト
	 * @param bPrettyPrint 整形するかどうか
	 * @return JSON文字列
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Convert", meta = (Keywords = "json to string"))
	static FString JsonToString(const FEasyJsonObjectV2& JsonObject, bool bPrettyPrint = true);

	// ========================================
	// ユーティリティ機能
	// ========================================

	/**
	 * JSONオブジェクトが有効かどうかを確認
	 * @param JsonObject JSONオブジェクト
	 * @return 有効な場合true
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Utility", meta = (Keywords = "json valid check"))
	static bool IsJsonObjectValid(const FEasyJsonObjectV2& JsonObject);

	/**
	 * 2つのJSONオブジェクトが等しいかどうかを確認
	 * @param JsonObjectA 比較するJSONオブジェクトA
	 * @param JsonObjectB 比較するJSONオブジェクトB
	 * @return 等しい場合true
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Utility", meta = (Keywords = "json equal compare"))
	static bool AreJsonObjectsEqual(const FEasyJsonObjectV2& JsonObjectA, const FEasyJsonObjectV2& JsonObjectB);

	// ========================================
	// デバッグ機能
	// ========================================

	/**
	 * デバッグモードを設定
	 * @param bEnabled デバッグモードを有効にするかどうか
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Debug", meta = (Keywords = "json debug mode"))
	static void SetDebugMode(bool bEnable);

	/**
	 * デバッグモードの状態を取得
	 * @return デバッグモードが有効な場合true
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Debug", meta = (Keywords = "json debug mode"))
	static bool IsDebugMode();

	/**
	 * デバッグログレベルを設定
	 * @param LogLevel 設定するログレベル
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyJsonParserV2|Debug", meta = (Keywords = "json debug log level"))
	static void SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel InLogLevel);

	/**
	 * 現在のデバッグログレベルを取得
	 * @return 現在のログレベル
	 */
	UFUNCTION(BlueprintPure, Category = "EasyJsonParserV2|Debug", meta = (Keywords = "json debug log level"))
	static EEasyJsonParserV2DebugLogLevel GetDebugLogLevel();
};