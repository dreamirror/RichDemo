#include "RichCameraManager.h"
#include "RichActor/RActorBase.h"
#include "CameraPawnBase.h"
#include "Framework/RGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

DEFINE_SINGLETON(FRichCameraManager, Init(), Destory());

void FRichCameraManager::Init()
{
}

void FRichCameraManager::InitData(URGameInstance* InGameInstance)
{
	RGameInstance = InGameInstance;
}

void FRichCameraManager::Destory()
{
	CameraPawnList.Empty();
	RGameInstance = nullptr;
	MainCameraPawn = nullptr;
}

bool FRichCameraManager::RegistRichCamera(ACameraPawnBase* InRCamera, FString CameraID, bool bMainCamera)
{
	if (auto Item = CameraPawnList.Find(CameraID))
	{
		if (ACameraPawnBase* CameraPawn = Cast<ACameraPawnBase>(*Item))//CameraPawnList.Find(CameraID))
			return false;
	}
	else //如果当前没有此分类，添加一个
		CameraPawnList.Add(CameraID, InRCamera);

	if (bMainCamera) {
		MainCameraPawn = InRCamera;
	}
	return true;
}

ACameraPawnBase* FRichCameraManager::GetRichCamera(FString CameraID)
{
	if (auto Item = CameraPawnList.Find(CameraID))
	{
		if (ACameraPawnBase* CameraPawn = Cast<ACameraPawnBase>(*Item))
			return CameraPawn;
	}
	
	
	return nullptr;
}

void FRichCameraManager::SetViewTarget(FString InCameraID, FViewTargetTransitionParams TransitionParams)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(RGameInstance,0))) {
		if (auto Item = CameraPawnList.Find(InCameraID))
		{
			if (ACameraPawnBase* CameraPawn = Cast<ACameraPawnBase>(*Item))//CameraPawnList.Find(InCameraID))
				PlayerController->SetViewTarget(CameraPawn, TransitionParams);
		}
	}
}
