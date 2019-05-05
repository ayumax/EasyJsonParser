#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/NoExportTypes.h"
#include "EasyJsonElement.h"
#include "EasyJsonAsyncLoadFromFile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEasyJsonAsyncLoadFromFile_Result, UEasyJsonElement*, JsonObject, FString, ErrorMessage);


UCLASS()
class EASYJsonPARSER_API UEasyJsonAsyncLoadFromFile : public UBlueprintAsyncActionBase
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