#include "DataConfigManager.h"
#include "AssetRegistryModule.h"
#include "ModuleManager.h"
#include "LogMacros.h"

UDataConfigManager::UDataConfigManager()
{
	bInitialized = true;
}
UDataConfigManager::~UDataConfigManager()
{

	RealseEditorInstance();

}


static UDataConfigManager* EditorInstance = nullptr;
UDataConfigManager* UDataConfigManager::GetEditorInstance()
{
	if (EditorInstance == nullptr)
	{
		EditorInstance = NewObject<UDataConfigManager>(GetTransientPackage(), TEXT("DataManager_EditorInstance"));
		EditorInstance->AddToRoot();
		EditorInstance->Initialize();
	}

	return EditorInstance;
}

void UDataConfigManager::RealseEditorInstance()
{
	if (EditorInstance)
	{
		EditorInstance->RemoveFromRoot();
		EditorInstance = nullptr;
	}
}

FScreenTipsComTableRow UDataConfigManager::GetScreenTipsComTableRowByID(int32 ID)
{
	FDataConfigMgrModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FDataConfigMgrModule>(FName("DataConfigMgr"));
	UDataConfigManager *DataInstance = AssetRegistryModule.MgrInstance;
	const FScreenTipsComTableRow* data = DataInstance->GetDataByID<FScreenTipsComTableRow>(1);
	FScreenTipsComTableRow outdata;
	outdata.ID = data->ID;
	outdata.name = data->name;
	outdata.Content = data->Content;
	return outdata;
}



UDataConfigManager* UDataConfigManager::Get(const UObject* WorldContextObject)
{
	/*
	UWorld* MyWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (MyWorld)
	{
		UPNGameInstance* GameInstance = Cast<UPNGameInstance>(MyWorld->GetGameInstance());
		if (GameInstance)
		{
			UPNDataConfigMgr* Out = GameInstance->GetDataConfigMgr();
			ensure(Out->bInitialized);
			return Out;
		}
	}
	*/
	return nullptr;
}

void UDataConfigManager::Initialize()
{

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	TArray<FAssetData> AllAssets;
	TArray<FString> PathsToScan;
	const FString FullPath = "/Game/ProjectN/Configs/Data";
	PathsToScan.Add(FullPath);
	AssetRegistry.ScanPathsSynchronous(PathsToScan);
	TArray<FAssetData> Assets;
	AssetRegistry.GetAssetsByPath(FName(*FullPath), Assets, true);
	TArray<UDataTable*> Out;
	for (FAssetData AD : Assets)
	{
		UDataTable* OutAsset = Cast<UDataTable>(AD.GetAsset());

		const UScriptStruct* StructPtr = OutAsset->GetRowStruct();
		if (StructPtr)
		{
			AssetDataContainer.Add(StructPtr, AD);
		}

		if (OutAsset)
		{
			Out.Add(OutAsset);
		}
	}


	for (UDataTable* DT : Out)
	{
		if (DT)
		{
			
			const UScriptStruct* StructPtr = DT->GetRowStruct();
			if (StructPtr && StructPtr->IsChildOf(FTableRow::StaticStruct()))
			{
				DataTableContainer.Add(StructPtr, DT);
				DT->AddToRoot();

				TArray<FTableRow*> Rows;
				FString CS("");
				DT->GetAllRows<FTableRow>(CS, Rows);

				if (Rows.Num() < 0)
				{
					UE_LOG(LogTemp, Warning,TEXT("配置表为空"));
					continue;
				}
				

				FDataTableContainer PNContainer;
				PNContainer.NameContainer.Reserve(Rows.Num());
				PNContainer.IDContainer.Reserve(Rows.Num());

				for (FTableRow* Row : Rows)
				{
					PNContainer.IDContainer.Add(Row->GetID(), reinterpret_cast<uint8*>(Row));
					PNContainer.NameContainer.Add(Row->GetName(), reinterpret_cast<uint8*>(Row));
				}

				//check(DataContainer.Contains(StructPtr) == false);
				DataContainer.Add(StructPtr, PNContainer);
			}
		}
	}

	bInitialized = true;
}

void UDataConfigManager::Shutdown()
{

}

const FTableRow* UDataConfigManager::GetDataByID(int32 ID, const UScriptStruct* DataClass) const
{
	if (DataClass == nullptr || DataClass->IsChildOf(FTableRow::StaticStruct()) == false)
		return nullptr;

	if (DataContainer.Contains(DataClass))
	{
		const FDataTableContainer& TC = DataContainer[DataClass];
		if (TC.HasData(ID))
		{
			return TC.GetData<FTableRow>(ID);
		}
	}

	// try to find in child struct 's container.
	TArray<const UScriptStruct*> Structs;
	DataContainer.GenerateKeyArray(Structs);
	for (const UScriptStruct* S : Structs)
	{
		if (S->IsChildOf(DataClass) && DataContainer[S].HasData(ID))
		{
			return DataContainer[S].GetData<FTableRow>(ID);
		}
	}


	return nullptr;
}

