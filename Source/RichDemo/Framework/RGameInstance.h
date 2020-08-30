// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RGameInstance.generated.h"

class URUIManager;
class URMaskManager;

UCLASS()
class URGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	virtual void OnStart() override;

	//关卡切换时显示的自定义Widget
	class UBaseWidget* LoadingWidget = nullptr;

	UPROPERTY()
	class URUIManager * MOUIManager = nullptr;

	UPROPERTY()
	class URMaskManager* MaskManager = nullptr;

	static URGameInstance* Instance;
public:
	static URGameInstance* Get() { return Instance; }
	virtual void Init() override;
	virtual void Shutdown() override;

	//开始加载关卡时回调
	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	//结束加载关卡时回调
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* LoadedWorld);

	UFUNCTION(BlueprintPure, Category = "RGameInstance")
	URUIManager* GetUIManager() const { return MOUIManager; }

	UFUNCTION(BlueprintPure, Category = "RGameInstance")
	URMaskManager* GetMaskManager() const { return MaskManager; }

};
