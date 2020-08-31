// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/BaseWidget.h"
#include "RichDefine.h"
#include "WG_MainMenu.generated.h"

UCLASS()
class UWG_MainMenu : public UBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnMenuButtonClick(EMainMenuType Parm);
};
