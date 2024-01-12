// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameUserSettings.h"
#include "NX_FrameComponent.generated.h"

#if PLATFORM_SWITCH
#include <nn/oe.h>
#endif


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NX_BPLIBRARY_API UNX_FrameComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	

	void UpdateFrameConfiguration();

public:	
	// Sets default values for this component's properties
	UNX_FrameComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
		APlayerController* OwningPlayer;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		bool d_UseDynRes = true;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		bool d_UseVSync = false;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		float d_MaxFPS= 60.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		float d_MinScreenPercent = 65.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		float d_MaxScreenPercent = 125.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		float d_FrameTimeBudget = 16.6f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Docked Properties")
		int d_OperationMode = 2;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		bool h_UseDynRes = true;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		bool h_UseVSync = true;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		float h_MaxFPS = 30.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		float h_MinScreenPercent = 50.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		float h_MaxScreenPercent = 100.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		float h_FrameTimeBudget = 33.3f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Handle Properties")
		int h_OperationMode = 2;
};
