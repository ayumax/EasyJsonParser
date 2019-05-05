#include "EasyJsonAsyncLoadFromString.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Async/Async.h"
#include "Utils/CustomJsonParser.h"

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
			CustomJsonParser parser;
			FString _errorMessage;

			auto rootElement = parser.Parse(_JsonString, _errorMessage);
			
			if (rootElement != nullptr)
			{
				AsyncTask(ENamedThreads::GameThread, [this, rootElement]()
					{
						Successed.Broadcast(rootElement, TEXT(""));
						SetReadyToDestroy();
					});
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, [this, _errorMessage]()
					{
						Failed.Broadcast(nullptr, _errorMessage);
						SetReadyToDestroy();
					});
			}

		});
}
