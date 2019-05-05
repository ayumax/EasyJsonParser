// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEasyJsonParserErrorCode : uint8
{
	Successed,
	Failed
};

UENUM(BlueprintType)
enum class EEasyJsonParserFound : uint8
{
	Found,
	NotFound
};