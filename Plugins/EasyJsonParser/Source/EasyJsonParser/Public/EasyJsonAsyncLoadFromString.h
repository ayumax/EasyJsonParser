#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/NoExportTypes.h"
#include "EasyJsonElement.h"
#include "EasyJsonAsyncLoadFromString.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEasyJsonAsyncLoadFromString_Result, UEasyJsonElement*, JsonObject, FString, ErrorMessage);


UCLASS()
class EASYJsonPARSER_API UEasyJsonAsyncLoadFromString : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FEasyJsonAsyncLoadFromString_Result Successed;

	UPROPERTY(BlueprintAssignable)
	FEasyJsonAsyncLoadFromString_Result Failed;

private:
	UPROPERTY(Transient)
	FString _JsonString;

public:
	UEasyJsonAsyncLoadFromString(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "EasyJsonParser", meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UEasyJsonAsyncLoadFromString* AsyncLoadFromString(UObject * WorldContextObject, const FString& JsonString);

	
	virtual void Activate() override;

};