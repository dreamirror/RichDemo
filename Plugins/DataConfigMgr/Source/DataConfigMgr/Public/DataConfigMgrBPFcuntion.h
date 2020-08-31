// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataConfigManager.h"

#include "DataConfigMgrBPFcuntion.generated.h"

/**
 * 
 */
UCLASS()
class DATACONFIGMGR_API UDataConfigMgrBPFcuntion : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintPure, Category = "DataConfigMgr")
		static UDataConfigManager* GetDataConfigMgrInstance();
};
