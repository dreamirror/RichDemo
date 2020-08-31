#pragma once
#include "ObjectMacros.h"
#include "Engine/DataTable.h"
#include "LogMacros.h"
#include "DataConfigMgr.h"
#include "PNDataConfigType.generated.h"
//DEFINE_LOG_CATEGORY(DataConfigManagerLog)


USTRUCT()
struct FTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FTableRow() {};

	virtual int32 GetID() const {  return -1; }
	virtual FName GetName() const {  return NAME_None; }
};

USTRUCT(BlueprintType)
struct FScreenTipsComTableRow :public FTableRow
{

	GENERATED_BODY()

public:
	FScreenTipsComTableRow():
		ID(-1)
	{}

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText name;

	//内容
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Content;

	virtual int32 GetID() const override { return ID; }
	virtual FName GetName() const override { return *name.ToString(); }
};

/**
 * 互动反馈字幕配置档
 */
USTRUCT(BlueprintType)
struct FFeedBackWordConfig : public FTableRow
{
	GENERATED_USTRUCT_BODY()

public:

	FFeedBackWordConfig()
		: ID(-1)
	{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText WordContent;

	virtual int32 GetID() const override { return ID; }
};

/*下一话的ID - path*/
USTRUCT(BlueprintType)
struct FFNextDlgData : public FTableRow {
	GENERATED_USTRUCT_BODY();
public:
	FFNextDlgData()
		:ID(-1)
	{};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "DlgDialogue"))
	FSoftObjectPath DlgPath;

	//该地图对应的Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "World"))
	FSoftObjectPath LevelPath;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FText name;

	//virtual FName GetName() const override { return *name.ToString(); }
	virtual int32 GetID() const override { return ID; }
};


USTRUCT(BlueprintType)
struct FStoryItem : public FTableRow
{
	GENERATED_BODY()

public:
	FStoryItem()
		:ID(-1)
	{};
	//默认第一列为主键，不配置
	//其余设置的是走第二列开始算的
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StoryItem")
		int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StoryItem")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StoryItem")
		bool bShowTop = false;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StoryItem")
	//TSoftObjectPtr<UTexture2D> ItemIcon;

	int32 GetID() const { return ID; }

	FString GetContent() const { return Description; }
};


UENUM()
enum class FFunctionParamType :uint8 //设置uint8类型  
{
	None,
	String,
	Numberic,
	Boolean,
};

/**
 * 条件系统判断函数配置表
 */
USTRUCT(BlueprintType)
struct FConditionFuncConfig : public FTableRow
{
	GENERATED_BODY()

public:
	FConditionFuncConfig()
		:ID(-1)
	{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConditionFuncInfo", SimpleDisplay = "ID")
		int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConditionFuncInfo", SimpleDisplay = "函数名")
		FString FunctionName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConditionFuncInfo", SimpleDisplay = "参数个数")
		int32 ParamCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConditionFuncInfo", SimpleDisplay = "参数类型")
		TArray<FFunctionParamType> ParamType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConditionFuncInfo", SimpleDisplay = "返回类型")
		FFunctionParamType ReturnType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConditionFuncInfo", SimpleDisplay = "描述")
		FString Desc;

	virtual int32 GetID() const override { return ID; }
};


UENUM()
enum class FValueType :uint8 //设置uint8类型  
{
	String,
	Numberic,
	Boolean,
};

/**
 * 默认值配置表
 */
USTRUCT(BlueprintType)
struct FCustomDefaultConfig : public FTableRow
{
	GENERATED_BODY()

public:
	FCustomDefaultConfig()
		:ID(-1)
		,KEY("")
		,ValueType(FValueType::Numberic)
		,NumbericValue(0.0)
		,BooleanValue(false)
		,StringValue("")
	{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomDefaultValue", SimpleDisplay = "ID")
		int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomDefaultValue", SimpleDisplay = "存储名字")
		FString KEY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomDefaultValue", SimpleDisplay = "存储类型")
		FValueType ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomDefaultValue", SimpleDisplay = "数值类型值")
		float NumbericValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomDefaultValue", SimpleDisplay = "布尔类型值")
		bool BooleanValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomDefaultValue", SimpleDisplay = "字符串值")
		FString StringValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomDefaultValue", SimpleDisplay = "描述")
		FString Desc;

	virtual int32 GetID() const override { return ID; }
};