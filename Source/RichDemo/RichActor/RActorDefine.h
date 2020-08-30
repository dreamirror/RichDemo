
#pragma once

#include "CoreMinimal.h"
#include "RActorDefine.generated.h"

/*
暂时已枚举的方式来展现，之后会使用配置表这样可以在编辑器里直接扩展的方式
*/
UENUM()
enum class ERActorType : uint8
{
	NONE = 0,
	UIONBUILD,			//3DUI
	OUTSIDECOVER,		//建筑外层遮罩Actor
	LIGHTROAD,			//流光路面

};