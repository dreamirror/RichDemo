#pragma once
#include "ObjectMacros.h"
#include "NoExportTypes.h"
#include "PNDataConfigType.h"
#include "CoreMinimal.h"
#include "AssetData.h"

#include "DataConfigManager.generated.h"
struct FDataTableContainer
{
	TMap<int32, uint8*> IDContainer;
	TMap<FName, uint8*> NameContainer;

	bool HasData(int32 ID) const
	{
		return IDContainer.Contains(ID);
	}
	bool HasData(const FName& Name) const
	{
		return NameContainer.Contains(Name);
	}

	template<typename TDataClass>
	const TDataClass* GetData(int32 ID) const;
	template<typename TDataClass>
	const TDataClass* GetData(const FName& Name) const;
};

template<typename TDataClass>
const TDataClass* FDataTableContainer::GetData(int32 ID) const
{
	return HasData(ID) ? reinterpret_cast<const TDataClass*>(IDContainer[ID]) : nullptr;
}

template<typename TDataClass>
const TDataClass* FDataTableContainer::GetData(const FName& Name) const
{
	return HasData(Name) ? reinterpret_cast<const TDataClass*>(NameContainer[Name]) : nullptr;
}


UCLASS()
class  UDataConfigManager : public UObject
{
	GENERATED_BODY()

public:
	UDataConfigManager();
	~UDataConfigManager();

	//UFUNCTION(BlueprintPure, Category = "PNDataManager")
	static UDataConfigManager* GetEditorInstance();
	static void TestStatcic() {};
	static void RealseEditorInstance();


	UFUNCTION(BlueprintPure, Category = "DataConfigMgr")
		FScreenTipsComTableRow GetScreenTipsComTableRowByID(int32 ID);



	static UDataConfigManager* Get(const UObject* WorldContextObject);

	void Initialize();
	void Shutdown();

	template<typename TDataClass>
	bool HasData(int32 ID) const;

	template<typename TDataClass>
	const TDataClass* GetDataByID(int32 ID) const;

	//更具结构体获取datatable
	template<typename TDataTableClass>
	const FAssetData GetAsseData() const;

	//刷新对应的表缓存
	template <typename TDataClass>
	bool ReloadDataTable();

	const FTableRow* GetDataByID(int32 ID, const UScriptStruct* DataClass) const;

	
	template<typename TDataClass>
	const TDataClass* GetDataByName(const FName& Name) const;

	//获取表的所有数据
	template<typename TDataClass>
	const TArray<TDataClass*> GetAllData()const;
private:

	//结构体和数据的索引
	TMap<const UScriptStruct*, FDataTableContainer> DataContainer;

	//结构体和Datatable的索引
	TMap<const UScriptStruct*, UDataTable*> DataTableContainer;

	//结构体和AssetData的索引
	TMap<const UScriptStruct*, FAssetData> AssetDataContainer;
	uint8 bInitialized : 1;

};

template<typename TDataClass>
bool UDataConfigManager::HasData(int32 ID) const
{
	UScriptStruct* StructPtr = TDataClass::StaticStruct();
	if (StructPtr == nullptr || StructPtr->IsChildOf(FTableRow::StaticStruct()) == false)
	{
		return false
	}
	if (DataContainer.Contains(StructPtr))
	{
		return DataContainer[StructPtr].HasData(ID);
	}
	Array<Const UScriptStruct*> Structs;
	DataContainer.GenerateKeyArray(Structs);
	for (const UScriptStruct* S : Structs)
	{
		if (S->IsChildOf(StructPtr) && DataContainer[S].HasData(ID))
		{
			return true;
		}
	}
	return false;


}

template<typename TDataClass>
const TDataClass* UDataConfigManager::GetDataByID(int32 ID) const
{
	UScriptStruct* StructPtr = TDataClass::StaticStruct();
	if (StructPtr == nullptr || StructPtr->IsChildOf(FTableRow::StaticStruct()) == false)
		return nullptr;

	if (DataContainer.Contains(StructPtr))
	{
		const FDataTableContainer& TC = DataContainer[StructPtr];
		if (TC.HasData(ID))
		{
			return TC.GetData<TDataClass>(ID);
		}
	}


	// try to find in child struct 's container.
	TArray<const UScriptStruct*> Structs;
	DataContainer.GenerateKeyArray(Structs);
	for (const UScriptStruct* S : Structs)
	{
		if (S->IsChildOf(StructPtr) && DataContainer[S].HasData(ID))
		{
			return DataContainer[S].GetData<TDataClass>(ID);
		}
	}


	return nullptr;
}

//根据tablerow 获取表的datatable
template<typename TDataTableClass>
const FAssetData UDataConfigManager::GetAsseData() const
{
	FAssetData ad;
	UScriptStruct* StructPtr = TDataTableClass::StaticStruct();
	if (StructPtr == nullptr || StructPtr->IsChildOf(FTableRow::StaticStruct()) == false)
		return ad;

	if (AssetDataContainer.Contains(StructPtr))
	{
		return AssetDataContainer[StructPtr];
	}
	return ad;
}


//刷新对应结构的缓存表
template <typename TDataClass>
bool UDataConfigManager::ReloadDataTable()
{

	UScriptStruct* StructPtr = TDataClass::StaticStruct();
	if (StructPtr == nullptr || StructPtr->IsChildOf(FTableRow::StaticStruct()) == false)
		return false;


	//check(AssetDataContainer.Contains(StructPtr) == false);

	FAssetData AD = AssetDataContainer[StructPtr];

	UDataTable* DT = Cast<UDataTable>(AD.GetAsset());

	if (DT)
	{

		TArray<FTableRow*> Rows;
		FString CS("");
		DT->GetAllRows<FTableRow>(CS, Rows);

		if (Rows.Num() < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("配置表为空"));
			return false;
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
		DataContainer[StructPtr] = PNContainer;
		
	}

	return true;
}

template<typename TDataClass>
const TDataClass* UDataConfigManager::GetDataByName(const FName& Name) const
{
	UScriptStruct* StructPtr = TDataClass::StaticStruct();
	if (StructPtr == nullptr || StructPtr->IsChildOf(FTableRow::StaticStruct()) == false)
		return nullptr;

	if (DataContainer.Contains(StructPtr))
	{
		const FPNDataTableContainer& TC = DataContainer[StructPtr];
		if (TC.HasData(Name))
		{
			return TC.GetData<TDataClass>(Name);
		}
	}

	// try to find in child struct 's container.
	TArray<const UScriptStruct*> Structs;
	DataContainer.GenerateKeyArray(Structs);
	for (const UScriptStruct* S : Structs)
	{
		if (S->IsChildOf(StructPtr) && DataContainer[S].HasData(Name))
		{
			return DataContainer[S].GetData<TDataClass>(Name);
		}
	}

	return nullptr;
}

template<typename TDataClass>
const TArray<TDataClass*>UDataConfigManager::GetAllData() const
{
	TArray<TDataClass*> OutArray;
	UScriptStruct* StructPtr = TDataClass::StaticStruct();
	if (StructPtr == nullptr || StructPtr->IsChildOf(FTableRow::StaticStruct()) == false)
	{
		return OutArray;
	}

	if (DataContainer.Contains(StructPtr))
	{
		const FDataTableContainer& TC = DataContainer[StructPtr];
		TMap<int32, uint8*> TT = TC.IDContainer;
		for (auto iter = TT.CreateIterator();iter;++iter)
		{
			TDataClass* data = (TDataClass*)iter->Value;
			OutArray.Add(data);
		}
	
	}

	return OutArray;
}
