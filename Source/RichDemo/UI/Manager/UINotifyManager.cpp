// Fill out your copyright notice in the Description page of Project Settings.


#include "UINotifyManager.h"

//.h中的静态变量必须在cpp中声明，否则编译报无法解析的外部符号
//FOnTestDelegate UUINotifyManager::OnTestDelegate = TMulticastDelegate<void, float, float>();
//借鉴CoreDelegates.cpp中声明static变量的方式
UUINotifyManager::FOnTestDelegate UUINotifyManager::OnTestDelegate;

UUINotifyManager::FOnMainCityInfoChangeDelegate UUINotifyManager::OnMainCityInfoChangeDelegate;