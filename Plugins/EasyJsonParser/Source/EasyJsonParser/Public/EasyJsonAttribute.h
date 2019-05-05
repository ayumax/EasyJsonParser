// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "EasyJsonObject.h"
#include "EasyJsonAttribute.generated.h"

class UEasyJsonElement;

UCLASS(BlueprintType, Blueprintable)
class EASYJsonPARSER_API UEasyJsonAttribute : public UEasyJsonObject
{
	GENERATED_BODY()
	
public:
	static UEasyJsonAttribute* CreateAttribute(UEasyJsonElement* ParentObject, FString Name, FString Value);

};
