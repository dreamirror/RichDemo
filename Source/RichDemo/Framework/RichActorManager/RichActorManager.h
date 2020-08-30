#pragma once

#include "Framework/Singleton.h"
#include "RichDemo/RichActor/RActorDefine.h"

class URGameInstance;
class ARActorBase;

/*
* 场景Actor管理系统
*/
class FRichActorManager
{
	DECLARE_SINGLETON(FRichActorManager);

public:
	bool RegistRichActor(ARActorBase* InRActor);

	TArray<ARActorBase*> GetAllRichActor(ERActorType InType);
	void SetRichActorActive(ERActorType InType , bool bActive);

private:
	void Init();

	void Destory();

private:
	TMap< ERActorType, TArray<ARActorBase*>> RichActorList;
};