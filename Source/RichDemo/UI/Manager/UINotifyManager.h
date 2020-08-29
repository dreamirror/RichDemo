// Fill out your copyright notice in the Description page of Project Settings.
//************************************************************************************************************************************************************************
//																																										//
//	Project Name:			UMG_Mgr																																		//
//	Author:					TangWenLong																																	//
//	Completion Date:		10/25/2019																																	//
//	Copyright Declaration:																																				//
//																																										//
//																																										//
//************************************************************************************************************************************************************************

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/DelegateCombinations.h"
#include "UINotifyManager.generated.h"

enum class EMainCityInfoType : uint8;
struct FMainCityInfo;
/**
 *
 */
UCLASS()
class UUINotifyManager : public UObject
{
	GENERATED_BODY()
public:

	//定义带参数的委托
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTestDelegate, float, FString);

	//监听主城信息变化
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMainCityInfoChangeDelegate, EMainCityInfoType, FMainCityInfo*);

	//创建delegate的实例
	static FOnTestDelegate OnTestDelegate;

	static FOnMainCityInfoChangeDelegate OnMainCityInfoChangeDelegate;
};
