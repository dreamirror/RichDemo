#include "RichCameraManager.h"
#include "RichActor/RActorBase.h"

DEFINE_SINGLETON(FRichCameraManager, Init(), Destory());

void FRichCameraManager::Init()
{

}

void FRichCameraManager::Destory()
{

}

bool FRichCameraManager::RegistRichActor(ARActorBase* InRActor)
{
	ERActorType ActorType = InRActor->GetActorType();
	if (TArray<ARActorBase*>* TempActorList = RichActorList.Find(ActorType))
	{
		TempActorList->Add(InRActor);
	}
	else //如果当前没有此分类，添加一个
	{
		TArray<ARActorBase*> NewActorArray;
		NewActorArray.Add(InRActor);
		RichActorList.Add(ActorType, NewActorArray);
	}
	return true;
}

TArray<ARActorBase*> FRichCameraManager::GetAllRichActor(ERActorType InType)
{
	if (TArray<ARActorBase*>* TempActorList = RichActorList.Find(InType))
		return *TempActorList;
	
	TArray<ARActorBase*> Temp;
	return Temp;
}

void FRichCameraManager::SetRichActorActive(ERActorType InType, bool bActive)
{
	if (TArray<ARActorBase*>* TempActorList = RichActorList.Find(InType))
	{
		for (int index = 0; index < TempActorList->Num(); index++)
		{
			if(bActive)
				(*TempActorList)[index]->OnActive();
			else
				(*TempActorList)[index]->OnDisActive();
		}
	}
		
}
