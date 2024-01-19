#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Engine/Engine.h"
#include "HAL/IConsoleManager.h"
#include "Containers/UnrealString.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameUserSettings.h"
#include "NX_FrameComponent.generated.h"

//Get the NX Librairie
#if PLATFORM_SWITCH
#include <nn/oe.h>
#endif

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NX_BPLIBRARY_API UNX_FrameComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	
	void ApplyNXFrameConfig();
	void CheckPlayMode();
	void ModeChanged();
	void PrintSavedConfigs();
	void PrintDebugText(FString Message, FColor Color, float Time);
	void ExecuteCmd(FString Cmd);

public:	
	// Sets default values for this component's properties
	
	UNX_FrameComponent();

	//Print OnScreenMessages of the selected config
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plugin Properties")
		bool DebugMode = false;

	//Docked Mode Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		bool d_UseDynRes = true;
	//Boost the CPU from 1020 MHz to 1785 MHz (SDEV only)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		bool d_UseOverclock = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		bool d_UseVSync = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		int d_MaxFPS = 60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		int d_MinScreenPercent = 55;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		int d_MaxScreenPercent = 125;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		float d_FrameTimeBudget = 16.6f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		int d_OperationMode = 2;

	//Handle Mode Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		bool h_UseDynRes = true;

	//Boost the CPU from 1020 MHz to 1785 MHz (SDEV only)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		bool h_UseOverclock = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		bool h_UseVSync = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		int h_MaxFPS = 60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		int h_MinScreenPercent = 45;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		int h_MaxScreenPercent = 85;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		float h_FrameTimeBudget = 33.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		int h_OperationMode = 2;

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsSwitchDocked;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bSaveModeState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bPlayModeSaved = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
