// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/NoExportTypes.h"
#include "EasyJsonObject.h"
#include "EasyJsonAsyncLoadFromFile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEasyJsonAsyncLoadFromFile_Result, UEasyJsonObject*, JsonObject);


UCLASS()
class EASYJSONPARSER_API UEasyJsonAsyncLoadFromFile : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FEasyJsonAsyncLoadFromFile_Result Successed;

	UPROPERTY(BlueprintAssignable)
		FEasyJsonAsyncLoadFromFile_Result Failed;

private:
	UPROPERTY(Transient)
		FString _JsonFile;
	UPROPERTY(Transient)
		bool _IsAblolute;

public:
	UEasyJsonAsyncLoadFromFile(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "EasyJsonParser", meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UEasyJsonAsyncLoadFromFile * AsyncLoadFromFile(UObject * WorldContextObject, const FString& FilePath, bool IsAblolute);


	virtual void Activate() override;

};