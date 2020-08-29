// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UINotifyManager.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

// UI窗体的显示类型
UENUM(BlueprintType)
enum class EUIShowMode : uint8
{
    //普通
    Normal,
    //反向切换
    ReverseChange,
    //隐藏其他
    HideOther
};

/*
UI传递的数据类。
子类继承来填充自己的数据，强转一下类型
*/
UCLASS(Blueprintable,BlueprintType)
class UUIData : public UObject
{
    GENERATED_BODY()
public:
    UUIData()
    {
    };
};


/**
 *
 */
UCLASS(Abstract)
class UBaseWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    //在createWidget之后，传参,初始化窗口属性。
    virtual void Init(UUIData* UIData)
    {
    };

    //主动打开窗口，addToViewPort前触发
    virtual void OnPreShow() { OnPreShowUI(); };

    //主动打开窗口触发
    virtual void OnShow() { OnShowUI(); };

    //被动隐藏之后再显示会触发
    virtual void OnReShow() { OnReShowUI(); };

    //被动隐藏会触发
    virtual void OnHide() { OnHideUI(); };

    //主动关闭窗口触发
    virtual void OnClose() { OnCloseUI(); };

    //--------------- 蓝图中的事件----------------------
    UFUNCTION(BlueprintImplementableEvent, Category = "UI Widget")
    void OnPreShowUI();

    UFUNCTION(BlueprintImplementableEvent, Category = "UI Widget")
    void OnShowUI();

    UFUNCTION(BlueprintImplementableEvent, Category = "UI Widget")
    void OnReShowUI();

    UFUNCTION(BlueprintImplementableEvent, Category = "UI Widget")
    void OnHideUI();

    UFUNCTION(BlueprintImplementableEvent, Category = "UI Widget")
    void OnCloseUI();

    //UI关闭的回调（也可以通过UIData传入关闭的回调）
    DECLARE_MULTICAST_DELEGATE(FUICloseCallBackDelegate);
    FUICloseCallBackDelegate OnUICloseCallBack;
public:
    virtual void Show() final;
    
    virtual void ReShow() final;
    
    virtual void Hide() final;
    
    virtual void Close() final;

    virtual void NativeConstruct() override;
    
    virtual void NativeDestruct() override;

    virtual void BindUIComponent();

    //播放UI动画处理
    virtual void DoShowAnimation();
    //UI动画播放结束
    virtual void DoCloseAnimation();

public:
    /**
      *  窗口属性，可在init()中对其初始化
     */
    //是否清空“栈集合”
    UPROPERTY(BlueprintReadWrite)
    bool bClearStack = false;

    //是否需要通用的遮罩层
    UPROPERTY(BlueprintReadWrite)
    bool bShowMask = false;

    //UI显示模式
    UPROPERTY(BlueprintReadWrite)
    EUIShowMode UIShowMode = EUIShowMode::Normal;

    //临时zorder
    UPROPERTY()
    int32 ZOrder;

    //默认所有窗口都是单例，特殊的如系统弹窗那种需要搞成实例的，会更改这个属性为true
    UPROPERTY()
    bool bInstance = false;
};
