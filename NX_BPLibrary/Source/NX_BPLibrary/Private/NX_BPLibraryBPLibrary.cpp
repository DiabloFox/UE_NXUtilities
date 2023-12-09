// Copyright Epic Games, Inc. All Rights Reserved.

#include "NX_BPLibraryBPLibrary.h"
#include "NX_BPLibrary.h"


UNX_BPLibraryBPLibrary::UNX_BPLibraryBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UNX_BPLibraryBPLibrary::NX_BPLibrarySampleFunction(float Param)
{
	return -1;
}

//Console Perfomance Nodes

bool UNX_BPLibraryBPLibrary::GetOperationMode()
{
	bool bIsSwitchDocked;
	#if PLATFORM_WINDOWS
		bIsSwitchDocked = true;
	#elif PLATFORM_SWITCH
		bIsSwitchDocked = nn::oe::GetOperationMode() == nn::oe::OperationMode_Console;
	#endif
	return bIsSwitchDocked;
}

bool UNX_BPLibraryBPLibrary::GetPerformanceMode()
{
	bool bIsSwitchBoostMode;
	#if PLATFORM_WINDOWS
		bIsSwitchBoostMode = true;
	#elif PLATFORM_SWITCH
		bIsSwitchBoostMode = nn::oe::GetOperationMode() == nn::oe::PerformanceMode_Boost;
	#endif
	return bIsSwitchBoostMode;
}

//App Infos Nodes

bool UNX_BPLibraryBPLibrary::GetIsDemoMode()
{
	bool bIsDemoMode;
	#if PLATFORM_WINDOWS
		bIsDemoMode = true;
	#elif PLATFORM_SWITCH
		bIsDemoMode = nn::oe::IsInStoreDemoModeEnabled;
	#endif
	return bIsDemoMode;
}