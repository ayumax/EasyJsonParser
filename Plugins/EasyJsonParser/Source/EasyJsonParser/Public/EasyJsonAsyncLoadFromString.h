// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/NoExportTypes.h"
#include "EasyJsonObject.h"
#include "EasyJsonAsyncLoadFromString.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEasyJsonAsyncLoadFromString_Result, UEasyJsonObject*, JsonObject);


UCLASS()
class EASYJSONPARSER_API UEasyJsonAsyncLoadFromString : public UBlueprintAsyncActionBase
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