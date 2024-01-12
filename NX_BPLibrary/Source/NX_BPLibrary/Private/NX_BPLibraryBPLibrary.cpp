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