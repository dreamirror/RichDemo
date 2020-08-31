
#pragma once

#define BERICH 1;


/*主界面按钮枚举*/
UENUM(BlueprintType)
enum class EMainMenuType : uint8
{
	EFirstMenu_Area,
	EFirstMenu_Sandbox,
	EFirstMenu_House,
	EFirstMenu_Outside,

	ESecondMenu_Equipment,
	ESecondMenu_Traffic,
	ESecondMenu_Business,
	ESecondMenu_Building,
	ESecondMenu_Road,
	ESecondMenu_Location,
	ESecondMenu_Closeup1,
	ESecondMenu_Closeup2,
	ESecondMenu_FreeControl,
};


