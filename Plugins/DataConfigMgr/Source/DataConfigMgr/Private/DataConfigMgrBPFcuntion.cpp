// Fill out your copyright notice in the Description page of Project Settings.


#include "DataConfigMgrBPFcuntion.h"

UDataConfigManager* UDataConfigMgrBPFcuntion::GetDataConfigMgrInstance()
{
	FDataConfigMgrModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FDataConfigMgrModule>(FName("DataConfigMgr"));
	UDataConfigManager *DataInstance = AssetRegistryModule.MgrInstance;
	return DataInstance;
}
