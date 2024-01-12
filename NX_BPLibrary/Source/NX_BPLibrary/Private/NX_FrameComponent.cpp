// Fill out your copyright notice in the Description page of Project Settings.


#include "NX_FrameComponent.h"

// Sets default values for this component's properties
UNX_FrameComponent::UNX_FrameComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNX_FrameComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UNX_FrameComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateFrameConfiguration();
}

void UNX_FrameComponent::UpdateFrameConfiguration()
{

	FString cmd_vsync;
	FString cmd_maxfps;
	FString cmd_minscreenpercent;
	FString cmd_maxscreenpercent;
	FString cmd_framebudget;
	FString cmd_operationmode;

	OwningPlayer = Cast<APlayerController>(GetOwner());
	bool bIsSwitchDocked;
	#if PLATFORM_WINDOWS
		bIsSwitchDocked = true;
	#elif PLATFORM_SWITCH
		bIsSwitchDocked = nn::oe::GetOperationMode() == nn::oe::OperationMode_Console;
	

		if (bIsSwitchDocked == true) {

			GEngine->GameUserSettings->SetDynamicResolutionEnabled(d_UseDynRes);

			cmd_vsync = FString::Printf(TEXT("r.VSync 0 %f"), d_UseVSync);

			cmd_maxfps = FString::Printf(TEXT("t.MaxFPS %f"), d_MaxFPS);

			cmd_minscreenpercent = FString::Printf(TEXT("r.DynamicRes.MinScreenPercentage %f"), d_MinScreenPercent);

			cmd_maxscreenpercent = FString::Printf(TEXT("r.DynamicRes.MaxScreenPercentage %f"), d_MaxScreenPercent);

			cmd_framebudget = FString::Printf(TEXT("r.DynamicRes.FrameTimeBudget %f"), d_FrameTimeBudget);

			cmd_operationmode = FString::Printf(TEXT("r.DynamicRes.OperationMode %f"), d_OperationMode);

		}else{

			GEngine->GameUserSettings->SetDynamicResolutionEnabled(h_UseDynRes);

			cmd_vsync = FString::Printf(TEXT("r.VSync 1 %f"), h_UseVSync);

			cmd_maxfps = FString::Printf(TEXT("t.MaxFPS %f"), h_MaxFPS);

			cmd_minscreenpercent = FString::Printf(TEXT("r.DynamicRes.MinScreenPercentage %f"), h_MinScreenPercent);

			cmd_maxscreenpercent = FString::Printf(TEXT("r.DynamicRes.MaxScreenPercentage %f"), h_MaxScreenPercent);

			cmd_framebudget = FString::Printf(TEXT("r.DynamicRes.FrameTimeBudget %f"), h_FrameTimeBudget);

			cmd_operationmode = FString::Printf(TEXT("r.DynamicRes.OperationMode %f"), h_OperationMode);
		}

		OwningPlayer->ConsoleCommand(cmd_vsync);
		OwningPlayer->ConsoleCommand(cmd_maxfps);
		OwningPlayer->ConsoleCommand(cmd_minscreenpercent);
		OwningPlayer->ConsoleCommand(cmd_maxscreenpercent);
		OwningPlayer->ConsoleCommand(cmd_framebudget);
		OwningPlayer->ConsoleCommand(cmd_operationmode);

		GEngine->GameUserSettings->ApplyNonResolutionSettings();
	#endif
}

void UNX_FrameComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}