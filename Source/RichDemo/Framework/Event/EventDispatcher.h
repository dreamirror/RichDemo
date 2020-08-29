// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#define DECLARE_MO_EVENT(EventName) \
	DECLARE_EVENT(FEventDispatcher, F##EventName) \
	F##EventName EventName;

#define DECLARE_MO_EVENT_OneParam(EventName, Param1Type) \
	DECLARE_EVENT_OneParam(FEventDispatcher, F##EventName, Param1Type) \
	F##EventName EventName;
/*
DECLARE_EVENT_TwoParams(OwningType, EventName, Param1Type, Param2Type)
DECLARE_EVENT_ThreeParams(OwningType, EventName, Param1Type, Param2Type, Param3Type)
DECLARE_EVENT_FourParams(OwningType, EventName, Param1Type, Param2Type, Param3Type, Param4Type)
DECLARE_EVENT_FiveParams(OwningType, EventName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type)
DECLARE_EVENT_SixParams(OwningType, EventName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type)
DECLARE_EVENT_SevenParams(OwningType, EventName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type)
DECLARE_EVENT_EightParams(OwningType, EventName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type, Param8Type)
DECLARE_EVENT_NineParams(OwningType, EventName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type, Param8Type, Param9Type)
*/



class FEventDispatcher
{
public:







	//DECLARE_MO_EVENT_OneParam(SelectedExportType, uint8)
	//DECLARE_MO_EVENT_OneParam(SelectedDebugType, uint8)
	DECLARE_MO_EVENT(Test)
	DECLARE_MO_EVENT(Export)
	//DECLARE_MO_EVENT(AddAnimation)
	//DECLARE_MO_EVENT(ExportSkeletonAndAnimation)




};

extern FEventDispatcher GEventDispatcher;

