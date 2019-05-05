#include "EasyJsonAsyncLoadFromFile.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Async/Async.h"
#include "Utils/CustomJsonParser.h"
#include "EasyJsonParseManager.h"

UEasyJsonAsyncLoadFromFile::UEasyJsonAsyncLoadFromFile(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UEasyJsonAsyncLoadFromFile *UEasyJsonAsyncLoadFromFile::AsyncLoadFromFile(UObject *WorldContextObject, const FString &FilePath, bool IsAblolute)
{
	auto Action = NewObject<UEasyJsonAsyncLoadFromFile>();
	Action->RegisterWithGameInstance(WorldContextObject);
	Action->_JsonFile = FilePath;
	Action->_IsAblolute = IsAblolute;

	return Action;
}

void UEasyJsonAsyncLoadFromFile::Activate()
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]() {
		auto manager = NewObject<UEasyJsonParseManager>();
		FString _errorMessage;
		EEasyJsonParserErrorCode _isSuccessed;
		auto rootElement = manager->LoadFromFile(_JsonFile, _IsAblolute, _isSuccessed, _errorMessage);

		if (_isSuccessed == EEasyJsonParserErrorCode::Successed)
		{
			AsyncTask(ENamedThreads::GameThread, [this, rootElement]() {
				Successed.Broadcast(rootElement, TEXT(""));
				SetReadyToDestroy();
			});
		}
		else
		{
			AsyncTask(ENamedThreads::GameThread, [this, _errorMessage]() {
				Failed.Broadcast(nullptr, _errorMessage);
				SetReadyToDestroy();
			});
		}
	});
}
