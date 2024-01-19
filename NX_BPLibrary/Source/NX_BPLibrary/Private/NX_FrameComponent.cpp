#include "NX_FrameComponent.h"

// Sets default values for this component's properties
UNX_FrameComponent::UNX_FrameComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UNX_FrameComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DebugMode == true) {
		PrintDebugText("NX_frame Component Debug Mode ON", FColor::Purple, 5.0f);

		PrintSavedConfigs();
	}
	else {

		PrintDebugText("NX_frame Component Debug Mode OFF", FColor::Red, 5.0f);

	}
}


// Called every frame
void UNX_FrameComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckPlayMode();
	ModeChanged();
	if (DebugMode == true) {
		//To help visualize the differents commands input
		PrintSavedConfigs();
	}
}

void UNX_FrameComponent::CheckPlayMode() {

#if PLATFORM_WINDOWS
	//If it's launch with Windows it just don't do anything and set the Docked to True in case of other setting trying to limit the framerate if not docked (Fail-Safe)
	bIsSwitchDocked = true;
	PrintDebugText("Can't apply NX Settings this is a Windows device!", FColor::Orange, 0.0f);

#elif PLATFORM_SWITCH
	bool FirstApplyDone = false;

	//This is one of the most important part of the code (the check of the Play mode) 
	bIsSwitchDocked = nn::oe::GetOperationMode() == nn::oe::OperationMode_Console;
	if (bPlayModeSaved == false) {
		bSaveModeState = bIsSwitchDocked;
		bPlayModeSaved = true;
		PrintDebugText("NX Play Mode Saved !", FColor::Yellow, 5.0f);
		ModeChanged();

		//When the game start this get executed to apply the selected config without having to change play mode
		if (FirstApplyDone == false) {
			ApplyNXFrameConfig();
			FirstApplyDone = true;
			}
		}
	#endif
}


void UNX_FrameComponent::ModeChanged(){
	
	if (bIsSwitchDocked == bSaveModeState) {
		//Mode didn't change
		PrintDebugText("Same NX Mode", FColor::Yellow, 0.0f);
	}
	else {
		//If the Play Mode (Docked / Handle) change this get called and apply the config and save the new mode
		ApplyNXFrameConfig();

		bPlayModeSaved = false;
		PrintDebugText("Play Mode Changed", FColor::Green, 5.0f);
	}
}


//Apply all the configs
void UNX_FrameComponent::ApplyNXFrameConfig() {
	#if PLATFORM_WINDOWS

	#elif PLATFORM_SWITCH
	if (bIsSwitchDocked == true) {

		//Everything about DynRes is Cmd but the activation is UserSettings ?! Why man ....
		GEngine->GameUserSettings->SetDynamicResolutionEnabled(d_UseDynRes);

		//I tried to use the "d_UseVSync ? TEXT("1") : TEXT("0"); but it was a mess and it was easier to make it with just a if ...
		if (d_UseVSync == true) {
			ExecuteCmd("r.VSync 1");
		}
		else {
			ExecuteCmd("r.VSync 0");
		}
		if (d_UseOverclock == true) {
			nn::oe::SetCpuOverclockEnabled(true);
		}
		else {
			nn::oe::SetCpuOverclockEnabled(false);
		}
		
		
		ExecuteCmd("t.MaxFPS " + FString::FromInt(d_MaxFPS));
		ExecuteCmd("r.DynamicRes.MinScreenPercentage " + FString::FromInt(d_MinScreenPercent));
		ExecuteCmd("r.DynamicRes.MaxScreenPercentage " + FString::FromInt(d_MaxScreenPercent));
		ExecuteCmd("r.DynamicRes.FrameTimeBudget " + FString::SanitizeFloat(d_FrameTimeBudget));
		ExecuteCmd("r.DynamicRes.OperationMode " + FString::FromInt(d_OperationMode));

		//This is for apply the DynRes State
		GEngine->GameUserSettings->ApplyNonResolutionSettings();

		PrintDebugText("NX Docked Config Applied", FColor::Purple, 5.0f);
	} else {
		GEngine->GameUserSettings->SetDynamicResolutionEnabled(h_UseDynRes);
		//Same here ...
		if (h_UseVSync == true) {
			ExecuteCmd("r.VSync 1");
		}
		else {
			ExecuteCmd("r.VSync 0");
		}

		nn::oe::SetCpuOverclockEnabled(h_UseOverclock);
		ExecuteCmd("t.MaxFPS " + FString::FromInt(h_MaxFPS));
		ExecuteCmd("r.DynamicRes.MinScreenPercentage " + FString::FromInt(h_MinScreenPercent));
		ExecuteCmd("r.DynamicRes.MaxScreenPercentage " + FString::FromInt(h_MaxScreenPercent));
		ExecuteCmd("r.DynamicRes.FrameTimeBudget " + FString::SanitizeFloat(h_FrameTimeBudget));
		ExecuteCmd("r.DynamicRes.OperationMode " + FString::FromInt(h_OperationMode));

		//This is for apply the DynRes State
		GEngine->GameUserSettings->ApplyNonResolutionSettings();

		PrintDebugText("NX Handle Config Applied", FColor::Purple, 5.0f);
	}
	#endif

}

//Help me during debug to pin point that the Execute Command in C++ is a mess
void UNX_FrameComponent::PrintSavedConfigs() {

	if (DebugMode == true) {
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Is NX Docked : %s"), bIsSwitchDocked ? TEXT("true") : TEXT("false")));

		if (bIsSwitchDocked == true) {
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Use Dynamic Resolution : %s"), d_UseDynRes ? TEXT("true") : TEXT("false")));
		#if PLATFORM_SWITCH
			if (nn::oe::IsCpuOverclockEnabled()) {
				GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Use Overclock : True")));
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Use Overclock : False")));
			}
			
		#endif

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Use VSync : %s"), d_UseVSync ? TEXT("true") : TEXT("false")));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Max FPS : " + FString::SanitizeFloat(d_MaxFPS)));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Min Screen Percent : %f"), d_MinScreenPercent));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Max Screen Percent : %f"), d_MaxScreenPercent));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Frame Budget : " + FString::SanitizeFloat(d_FrameTimeBudget)));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Operation Mode : %i"), d_OperationMode));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Use Dynamic Resolution : %s"), h_UseDynRes ? TEXT("true") : TEXT("false")));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Use VSync : %s"), h_UseVSync ? TEXT("true") : TEXT("false")));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Max FPS : " + FString::SanitizeFloat(h_MaxFPS)));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Min Screen Percent : %f"), h_MinScreenPercent));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Max Screen Percent : %f"), h_MaxScreenPercent));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Frame Budget : " + FString::SanitizeFloat(h_FrameTimeBudget)));

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Operation Mode : %i"), h_OperationMode));
		}
	}
}

//I made this Function to make the code more readable 
void UNX_FrameComponent::PrintDebugText(FString Message, FColor Color, float Time) {
	//Only show if the Debug Mode is activated to not flood the Logs when i'm not working on this plugin / Component
	if (DebugMode == true) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		GEngine->AddOnScreenDebugMessage(-1, Time, Color, (Message));
	}
}

//Have to try at least 4 differents methods to make it work !!!
//It's really a pain in the A$$ that DynRes settings are only with cmd .-.
void UNX_FrameComponent::ExecuteCmd(FString Cmd) {
	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PController)
	{
		PController->ConsoleCommand((Cmd), true);
		FString AppendedCmd = "Command Executed" + Cmd;
		//Yeah I love Print
		PrintDebugText(AppendedCmd, FColor::Purple, 0.0f);
	}
}