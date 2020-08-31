// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RichDefine.h"


#define DECLARE_RICH_EVENT(EventName) \
	DECLARE_EVENT(FEventDispatcher, F##EventName) \
	F##EventName EventName;

#define DECLARE_RICH_EVENT_OneParam(EventName, Param1Type) \
	DECLARE_EVENT_OneParam(FEventDispatcher, F##EventName, Param1Type) \
	F##EventName EventName;




class FEventDispatcher
{
public:

	DECLARE_RICH_EVENT_OneParam(OnMainMenuClicked, EMainMenuType)
	


};

extern FEventDispatcher GEventDispatcher;

