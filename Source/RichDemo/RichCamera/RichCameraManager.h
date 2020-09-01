#pragma once

#include "Framework/Singleton.h"
#include "Camera/PlayerCameraManager.h"

class URGameInstance;
class ACameraPawnBase;

/*
* 场景camera管理系统, 以当前场景中的CameraID作为key，每个CameraID不可重复
*/
class FRichCameraManager
{
	DECLARE_SINGLETON(FRichCameraManager);

public:
	void InitData(URGameInstance* InGameInstance);

	bool RegistRichCamera(ACameraPawnBase* InRCamera , FString CameraID, bool bMainCamera = false);

	ACameraPawnBase* GetRichCamera(FString CameraID);
	void SetViewTarget(FString InCameraID , FViewTargetTransitionParams TransitionParams);

private:
	void Init();

	void Destory();

private:
	URGameInstance* RGameInstance;
	TMap< FString, ACameraPawnBase*> CameraPawnList;
	ACameraPawnBase* MainCameraPawn;
};