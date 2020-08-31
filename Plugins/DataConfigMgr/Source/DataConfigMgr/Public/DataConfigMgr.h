// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UDataConfigManager;
//DECLARE_LOG_CATEGORY_EXTERN(DataConfigManagerLog, Log, All)
class FDataConfigMgrModule : public IModuleInterface
{
public:
	UDataConfigManager* MgrInstance;
	/** IModuleInterface implementation */
	int test = 0;
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
