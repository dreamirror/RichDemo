
#pragma once

#include "CoreMinimal.h"
#include "RichActor/RActorBase.h"
#include "RichActor/RActorDefine.h"
#include "RBuildingCoverActor.generated.h"

/*
点击UI可以切换镜头的Actor类
*/

class ACameraActor;
class ACameraPawnBase;

UCLASS()
class ARBuildingCoverActor : public ARActorBase
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* Cover;

public:	
	ARBuildingCoverActor();
	~ARBuildingCoverActor();
public:	
    virtual void Tick(float DeltaSeconds) override;

	virtual void OnActive() override;
	virtual void OnDisActive() override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

	virtual void Init() override;

protected:

};
