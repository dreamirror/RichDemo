
#pragma once

#include "CoreMinimal.h"
#include "RichActor/RActorBase.h"
#include "RichActor/RActorDefine.h"
#include "Camera/PlayerCameraManager.h"
#include "RCutToCameraActor.generated.h"

/*
点击UI可以切换镜头的Actor类
*/

class ACameraActor;
class ACameraPawnBase;

UCLASS()
class ARCutToCameraActor : public ARActorBase
{
	GENERATED_BODY()
	
public:	
	ARCutToCameraActor();
	~ARCutToCameraActor();
public:	
    virtual void Tick(float DeltaSeconds) override;

	virtual void OnActive() override;
	virtual void OnDisActive() override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

	virtual void Init() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acotr相关属性", meta = (DisplayName = "要切换的相机"))
	ACameraPawnBase* CameraToCutTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acotr相关属性", meta = (DisplayName = "相机切换参数"))
	FViewTargetTransitionParams CameraTranParam;


	
};
