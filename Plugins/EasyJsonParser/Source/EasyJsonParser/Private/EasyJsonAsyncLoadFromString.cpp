// Copyright 2019 ayumax. All Rights Reserved.
#include "EasyJsonAsyncLoadFromString.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Async/Async.h"
#include "EasyJsonParseManager.h"

UEasyJsonAsyncLoadFromString::UEasyJsonAsyncLoadFromString(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

UEasyJsonAsyncLoadFromString* UEasyJsonAsyncLoadFromString::AsyncLoadFromString(UObject* WorldContextObject, const FString& JsonString)
{
	auto Action = NewObject<UEasyJsonAsyncLoadFromString>();
	Action->RegisterWithGameInstance(WorldContextObject);
	Action->_JsonString = JsonString;

	return Action;
}

void UEasyJsonAsyncLoadFromString::Activate()
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
		{
			auto manager = NewObject<UEasyJsonParseManager>();
			EEasyJsonParserErrorCode _isSuccessed;

			auto rootElement = manager->LoadFromString(_JsonString, _isSuccessed);
			
			if (_isSuccessed == EEasyJsonParserErrorCode::Successed)
			{
				AsyncTask(ENamedThreads::GameThread, [this, rootElement]()
					{
						Successed.Broadcast(rootElement);
						SetReadyToDestroy();
					});
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, [this]()
					{
						Failed.Broadcast(nullptr);
						SetReadyToDestroy();
					});
			}

		});
}
