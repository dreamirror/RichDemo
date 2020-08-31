// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "RMaskManager.generated.h"

class UUserWidget;

const FString MaskUI = TEXT("/Game/MO/UI/Blueprint/WidgetBP/WB_Mask.WB_Mask_C");

UCLASS()
class URMaskManager : public UObject
{
	GENERATED_BODY()

public:
	void InitMask(UWorld* world);
	void Shutdown();

	static URMaskManager* Get();

	UFUNCTION()
	void SetMaskLayer(int32 Layer);

	/*revert to last layer*/
	void RevertMaskLayer();

	UFUNCTION()
	void CancelMaskLayer();

protected:
	//hold the mask handle
	UPROPERTY()
	UUserWidget* MaskPanel;

	int32 PreLayer = 0;
	int32 CurLayer = 0;

	bool bInit = false;
};
