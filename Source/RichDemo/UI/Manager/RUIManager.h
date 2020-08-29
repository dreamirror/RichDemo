// Fill out your copyright notice in the Description page of Project Settings.
//************************************************************************************************************************************************************************
//																																										//
//	Project Name:			UMG_Mgr																																		//
//	Author:					TangWenLong																																	//
//	Completion Date:		10/25/2019																																	//
//	Copyright Declaration:																																				//
//																																										//
//																																										//
//************************************************************************************************************************************************************************

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RUIManager.generated.h"

class UBaseWidget;
class UUIData;


/*
窗口大部分是单例，即一个类一个窗口。个别的如通用二级弹窗或者提示框这种需要按实例处理。
提供了 ShowUI   ShowUIInstance 来区分这两种情况。
约定
1 : UI窗口不能同时可作为单例和多实例使用。即，如果一个窗口被设定为单例，则整个游戏过程中他都只有一个实例可用,不能通过创建多个实例的方式使用这个类型。
2 : 层级只影响显示的先后，可以根据需求再加
3 ：窗口属性中设定了窗口的显示属性，模态或者共存或者顶掉其他。也就是说会根据显示类型对窗口分类。
4 : 模态和跳转跳回不同，它只是暂时隐藏上一个窗口而已，关闭了会把上一个再显示出来；而跳转跳回此方案通过绑定窗口的关闭回调来实现。

层级层级越大显示越前。
*/
UENUM(BlueprintType)
enum class EUILayer :uint8
{
    //基础UI层，一般放全屏界面或者第一级界面。
    Base,
    //固定UI层，一般放那种可以同时显示几个的UI。
    Fixed,
    //弹窗层，二级弹窗，确认窗之类
    Popups,
    //系统级弹窗，断网啊，全服公告啊之类的，比普通弹窗更靠前
    SysBox,
    //提示文字之类
    Tips,
};

//存贮所有窗口
USTRUCT()
struct FUILayerWidget
{
    GENERATED_BODY()
public:
    FUILayerWidget()
    {
    };
    UPROPERTY()
    TArray<UBaseWidget*> UIs;
};

UCLASS(BlueprintType)
class URUIManager : public UObject
{
    GENERATED_BODY()
private:
    bool bInitialized;

    UWorld* World = nullptr;

    //打开过的UI
    UPROPERTY()
    TMap<FString, UBaseWidget*> OpenedUIMap;

    //正在显示的UI
    UPROPERTY()
    TMap<FString, UBaseWidget*> OpeningUIMap;

public:

    URUIManager();

    void Init(const UObject* WorldContextObject);

    void Shutdown();

    static URUIManager* Get();
    //===========================蓝图相关接口=================================================================================
    UFUNCTION(BlueprintPure, Category = "MOUIManager", meta = (WorldContext = "WorldContextObject"))
    static URUIManager* GetUIManager(const UObject* WorldContextObject);

    //蓝图 显示UMG界面，单例UI
    UFUNCTION(BlueprintCallable, Category = "MOUIManager")
    UBaseWidget* ShowWidget(TSubclassOf<UBaseWidget> UserWidgetClass, EUILayer Layer = EUILayer::Base,
                         UUIData* UIData = nullptr);

    //蓝图 显示UMG界面，实例UI
    UFUNCTION(BlueprintCallable, Category = "MOUIManager")
    UBaseWidget* ShowWidgetInstance(TSubclassOf<UBaseWidget> UserWidgetClass, EUILayer Layer = EUILayer::Base,
                                 UUIData* UIData = nullptr);

    //蓝图 根据类型获取所有UI实例并关闭。关闭单个建议使用 CloseUserWidget
    UFUNCTION(BlueprintCallable, Category = "MOUIManager")
    void CloseWidgetByClass(TSubclassOf<UBaseWidget> UserWidgetClass);

    //蓝图 关闭指定实例
    UFUNCTION(BlueprintCallable, Category = "MOUIManager")
    void CloseWidget(UBaseWidget* InWidget);

    //蓝图 根据类型获取所有缓存UI实例。
    UFUNCTION(BlueprintPure, Category = "MOUIManager")
    void GetCacheUIByClassInBP(TSubclassOf<UBaseWidget> WidgetSubClass, TArray<UBaseWidget*>& OutUIs) const;

    UFUNCTION()
    EUILayer GetUILayerInBP(UBaseWidget* Widget);

    //UI是否在缓存中
    UFUNCTION()
    bool IsUiInCache(UBaseWidget* UI);

    //===========================CPP相关接口=================================================================================
    //CPP 显示UMG界面，UI单例
    template <typename WidgetT>
    UBaseWidget* ShowUI(EUILayer Layer = EUILayer::Base, UUIData* UIData = nullptr)
    {
        UE_LOG(LOG_UMG, Log, TEXT("UMOUIManager::ShowWidget"));

        UBaseWidget* UWG_Cache = GetCacheUISingleton<WidgetT>();
        if (nullptr != UWG_Cache)
        {
            return ShowUiInner(UWG_Cache, Layer, UIData, true);
        }

        FString UIName = ConvertUserWidgetNameFromUClass(WidgetT::StaticClass());
        if (!UIName.IsEmpty())
        {
            return ShowUiInner(LoadUserWidget<WidgetT>(), Layer, UIData, false);
        }

        return nullptr;
    }

    //CPP 显示UMG界面，UI实例
    template <typename WidgetT>
    UBaseWidget* ShowUIInstance(EUILayer Layer = EUILayer::Base, UUIData* UIData = nullptr)
    {
        UE_LOG(LOG_UMG, Log, TEXT("UMOUIManager::ShowWidgetInstance"));

        FString UIName = ConvertUserWidgetNameFromUClass(WidgetT::StaticClass());
        if (!UIName.IsEmpty())
        {
            UBaseWidget* uwg = LoadUserWidget<WidgetT>();
            if (uwg)
            {
                uwg->bInstance = true;
            }
            return ShowUiInner(uwg, Layer, UIData);
        }
        return nullptr;
    }

    //CPP 加载UMG蓝图
    template <typename WidgetT>
    UBaseWidget* LoadUserWidget()
    {
        FString BasePath = MOGame::BP_UI_PATH;
        FString UIPath = "";

        FString UIName = ConvertUserWidgetNameFromUClass(WidgetT::StaticClass());
        if (!UIName.IsEmpty())
            UIPath = BasePath + UIName + "." + UIName + "_C'";

        if (UIPath.IsEmpty())
            return nullptr;

        TSubclassOf<UBaseWidget> WidgetClass = LoadClass<UBaseWidget>(nullptr, *UIPath);

        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
        //通过蓝图的类，创建UI
        UBaseWidget* UserWidget = nullptr;
        if (PlayerController)
            UserWidget = CreateWidget<UBaseWidget>(PlayerController, WidgetClass);

        return UserWidget;
    }

    //关闭UI实例显示。
    void CloseUI(UBaseWidget* UI);

    //"传类型可能会关闭同一类型的多个窗口实例，关闭单个建议使用 CloseWidget"
    template <typename WidgetT>
    void CloseUI()
    {
        UE_LOG(LOG_UMG, Log, TEXT("UMOUIManager::CloseWidgetByClass->"));
        CloseWidgetByClass(WidgetT::StaticClass());
    }

    void DestoryAllUI(ULevel* InLevel = nullptr, UWorld* InWorld = nullptr);
private:
    //显示UI AddToViewport
    UBaseWidget* ShowUiInner(UBaseWidget* UI, EUILayer Layer = EUILayer::Base, UUIData* UIData = nullptr,
                          bool bShowAgain = false);

    //将UClass名称转换成UMG蓝图名称，用于加载UMG蓝图
    FString ConvertUserWidgetNameFromUClass(UClass* UIClass);

    //获取根据UI类缓存的UI单例。
    template <typename WidgetT>
    UBaseWidget* GetCacheUISingleton()
    {
        TArray<UBaseWidget*> OutUIs;
        GetCacheUIByClassInBP(WidgetT::StaticClass(), OutUIs);
        for (UBaseWidget* var : OutUIs) //如果按照约定，这里其实只会获取到一个或者0个widget
        {
            if (var->bInstance == false)
                return var;
        }
        return nullptr;
    }

    //显示该UI且隐藏其他UI
    void ShowUIAndHideOther(UBaseWidget* UI);

    //关闭当前UI,显示其他UI
    void CloseUIAndShowOther(UBaseWidget* UI);

    //缓存打开过但关闭了的UI
    void AddUIToCache(UBaseWidget* UI);

    //从缓存中移除UI
    void RemoveUIFromCache(UBaseWidget* UI);

    //添加UI到“正在显示”的UI集合
    void AddOpeningUI(UBaseWidget* UI);

    //从“正在显示”的UI集合中移除
    void RemoveOpeningUI(UBaseWidget* UI);

    //将UI添加到"互斥栈"
    void PushUIToStack(UBaseWidget* UI);

    //将UI从”互斥栈”中移除
    void PopUIOutStack(UBaseWidget* UI);

    //清空“互斥栈”
    void ClearStackArray();

private:

    UPROPERTY(Transient)
    APlayerController* PController = nullptr;

    //缓存所有打开过但是当前未显示的UI窗体
    UPROPERTY(Transient)
    TMap<EUILayer, FUILayerWidget> CacheUIMap;

    //当前正在显示的UI窗体
    UPROPERTY(Transient)
    TArray<UBaseWidget*> OpeningUIArr;

    //定义”互斥栈“集合,存储显示当前所有[反向切换]的窗体类型
    UPROPERTY(Transient)
    TArray<UBaseWidget*> MutexUIArr;
};
