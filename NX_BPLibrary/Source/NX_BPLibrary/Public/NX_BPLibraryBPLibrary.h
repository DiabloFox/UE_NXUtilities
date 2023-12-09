// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NX_BPLibraryBPLibrary.generated.h"

#if PLATFORM_SWITCH
#include <nn/oe.h>
#endif

UCLASS()
class UNX_BPLibraryBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	//Plugin Testing Functions
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "NX_BPLibrary sample test testing"), Category = "NX_BPLibrary|Testing")
	static float NX_BPLibrarySampleFunction(float Param);

	//Console Infos Functions


	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get IsDocked", Keywords = "NX_BPLibrary"), Category = "NX_BPLibrary|ConsoleInfos")
	static bool GetOperationMode();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get IsBoost", Keywords = "NX_BPLibrary"), Category = "NX_BPLibrary|ConsoleInfos")
	static bool GetPerformanceMode();

	//App Infos Functions

	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get IsDemoMode", Keywords = "NX_BPLibrary"), Category = "NX_BPLibrary|AppInfos")
	static bool GetIsDemoMode();
};
