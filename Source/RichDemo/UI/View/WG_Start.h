// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/BaseWidget.h"
#include "WG_Start.generated.h"

/**
 * 
 */
UCLASS()
class UWG_Start : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnClickUnlock();

	UFUNCTION(Blueprintpure)
	bool UnlockBtnVisible();
};
