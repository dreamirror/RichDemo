
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RActorDefine.h"
#include "RActorBase.generated.h"

/*
场景中所有LevelActor的基类，没有使用接口是因为暂时没有想到会有需要其他非LevelActor引用的情况
*/
UCLASS()
class ARActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ARActorBase();
	~ARActorBase();
public:	
    virtual void Tick(float DeltaSeconds) override;
#if WITH_EDITOR
    virtual bool ShouldTickIfViewportsOnly() const override;
#endif
	UFUNCTION(BlueprintCallable)
	virtual void OnActive();
	UFUNCTION(BlueprintCallable)
	virtual void OnDisActive();

	UFUNCTION(BlueprintImplementableEvent, Category = "Rich Actor")
	void BP_OnActive();
	UFUNCTION(BlueprintImplementableEvent, Category = "Rich Actor")
	void BP_OnDisActive();

	ERActorType GetActorType() { return ActorType; };

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

	virtual void Init();

private:
	void RegistIntoManager();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "RActor基础信息" , meta= (DisplayName = "类型"))
	ERActorType ActorType;

};
