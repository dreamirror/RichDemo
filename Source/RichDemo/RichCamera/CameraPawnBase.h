// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawnBase.generated.h"


USTRUCT(BlueprintType)
struct FViewLimit
{
	GENERATED_BODY()

public:
	//meta=(UIMin=1, ClampMin=1, ClampMax=1024)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "垂直最大角度"))
	float ViewPitchMax = 89.9f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "垂直最小角度"))
	float ViewPitchMin = -89.9f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "水平最大角度"))
	float ViewYawMax = 89.9f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "水平最小角度"))
	float ViewYawMin = -89.9f;
};

/**
 * 相机基础类型，继承于pawn,可以使用AI驱动，且不直接使用CameraActor方便之后的漫游模式绑定到Character身上
 */
UCLASS()
class ACameraPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawnBase();

	virtual FRotator GetViewRotation() const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetViewRotation(const FRotator& Rot);
	virtual void UpdatePawnRotation(float DeltaTime);

	/** Called when this actor becomes the given PlayerController's ViewTarget. Triggers the Blueprint event K2_OnBecomeViewTarget. */
	virtual void BecomeViewTarget(class APlayerController* PC) override;

	/** Called when this actor is no longer the given PlayerController's ViewTarget. Also triggers the Blueprint event K2_OnEndViewTarget. */
	virtual void EndViewTarget(class APlayerController* PC) override;

private:
	void RegistToCameraManager();

public:

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "相机参数", meta = (DisplayName = "相机FOV"))
	FViewLimit CameraFovSetting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "相机参数", meta = (DisplayName = "是否设置为主相机" , DisplayAfter = "Transform"))
	bool bMainCamera = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "相机参数", meta = (DisplayName = "相机ID", DisplayAfter = "Transform"))
	FString CameraID;

private:
	bool bStartTick = false;
	


};
