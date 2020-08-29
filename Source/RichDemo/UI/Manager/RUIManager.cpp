#include "RUIManager.h"
#include "BaseWidget.h"
#include "RGameInstance.h"


void URUIManager::Init(const UObject* WorldContextObject)
{
	if (bInitialized)
		return;
	bInitialized = true;

    if (!WorldContextObject)
        return;
    World = WorldContextObject->GetWorld();

	CacheUIMap.Reset();
	FWorldDelegates::LevelRemovedFromWorld.AddUObject(this, &URUIManager::DestoryAllUI);
}

void URUIManager::Shutdown()
{
	PController = nullptr;
	DestoryAllUI();

    if (!IsPendingKill())
    {
        CacheUIMap.Empty();
        OpeningUIArr.Empty();
        MutexUIArr.Empty();
        bInitialized = false;
        World = nullptr;
    }
}

//测试结果是每个AActor的无参构造函数在UE4编辑器启动时就会被实例化this为Default_类名
URUIManager::URUIManager()
{
}

URUIManager* URUIManager::Get()
{
    return URGameInstance::Get()->GetUIManager();
}

URUIManager* URUIManager::GetUIManager(const UObject* WorldContextObject)
{
    return Get();
}

UBaseWidget* URUIManager::ShowUiInner(UBaseWidget* UI, EUILayer Layer, UUIData* UIData, bool bShowagain)
{
    if (nullptr == UI)
        return nullptr;

    int32 ZOrder = 0;

    //显示缓存的UI。
    if (bShowagain)
    {
        const EUILayer ShowLayer = GetUILayerInBP(UI);
        CacheUIMap[ShowLayer].UIs.Remove(UI);
        UI->RemoveFromParent();

        if (OpeningUIArr.Find(UI) != INDEX_NONE)
            OpeningUIArr.Remove(UI);

        if (MutexUIArr.Find(UI) != INDEX_NONE)
            MutexUIArr.Remove(UI);
    }
    //加入全局缓存
    if (CacheUIMap.Contains(Layer))
    {
        ZOrder = (int8)Layer * 50 + CacheUIMap[Layer].UIs.Num();
        CacheUIMap[Layer].UIs.Add(UI);
    }
    else
    {
        FUILayerWidget LayerWidgets;
        LayerWidgets.UIs.Add(UI);
        CacheUIMap.Add(Layer, LayerWidgets);
        ZOrder = (int8)Layer * 50;
    }

    UI->ZOrder = ZOrder;
    UI->Init(UIData);
    UI->OnPreShow();
    UI->AddToViewport(ZOrder);
    UI->Show();

    if (UI->bClearStack == true) //是否清空“互斥栈集合”中得数据
        ClearStackArray();

    switch (UI->UIShowMode)
    {
    case EUIShowMode::Normal:
        AddOpeningUI(UI); //加入“当前打开”缓存
        break;
    case EUIShowMode::ReverseChange:
        PushUIToStack(UI); //模态，这个不加到当前打开缓存中
        break;
    case EUIShowMode::HideOther:
        ShowUIAndHideOther(UI); //关闭其他，并把自己加到当前打开缓存
        break;
    default:
        break;
    }

    return UI;
}

UBaseWidget* URUIManager::ShowWidget(TSubclassOf<UBaseWidget> UserWidgetClass, EUILayer Layer, UUIData* UIData)
{
    if (UserWidgetClass == nullptr)
    {
        UE_LOG(LogTemp, Log, TEXT("ShowUserWidget->nullptr"));
        return nullptr;
    }
    UE_LOG(LogTemp, Log, TEXT("ShowUserWidget->%s"), *(UserWidgetClass->GetName()));

    TArray<UBaseWidget*> OutUIs;
    GetCacheUIByClassInBP(UserWidgetClass, OutUIs);
    UBaseWidget* const* UWG_Cache = OutUIs.FindByPredicate([](const UBaseWidget* CompareWidget)
    {
        return CompareWidget->bInstance == false;
    });

    if (UWG_Cache)
        return ShowUiInner(*UWG_Cache, Layer, UIData, true);

    UBaseWidget* UserWidget = nullptr;
	PController = UGameplayStatics::GetPlayerController(World, 0);
    if (PController)
        UserWidget = CreateWidget<UBaseWidget>(PController, UserWidgetClass);
    if (nullptr != UserWidget)
        return ShowUiInner(UserWidget, Layer, UIData, false);
    return nullptr;
}

UBaseWidget* URUIManager::ShowWidgetInstance(TSubclassOf<UBaseWidget> UserWidgetClass, EUILayer Layer, UUIData* UIData)
{
    UBaseWidget* UserWidget = nullptr;
	PController = UGameplayStatics::GetPlayerController(World, 0);
    if (PController)
        UserWidget = CreateWidget<UBaseWidget>(PController, UserWidgetClass);
    if (nullptr != UserWidget)
    {
        UserWidget->bInstance = true;
        return ShowUiInner(UserWidget, Layer, UIData, false);
    }
    return nullptr;
}

FString URUIManager::ConvertUserWidgetNameFromUClass(UClass* UIClass)
{
    FString TempUIName = "";
    if (UIClass == nullptr)
        return TempUIName;

    if (UIClass != nullptr)
        TempUIName = UIClass->GetName();

    if (!TempUIName.IsEmpty())
    {
        //把WG_替换成WB_
        if (TempUIName.StartsWith("WG_"))
            TempUIName = TempUIName.Replace(TEXT("WG_"), TEXT("WB_"), ESearchCase::CaseSensitive);
        //截取右边的_C字符
        if (TempUIName.EndsWith("_C"))
            TempUIName = TempUIName.LeftChop(2);
    }
    //UE_LOG(LogTemp, Log, TEXT("UIName->%s"), *TempUIName);
    return TempUIName;
}

void URUIManager::GetCacheUIByClassInBP(TSubclassOf<UBaseWidget> WidgetClass, TArray<UBaseWidget*>& OutUIs) const
{
    UE_LOG(LogTemp, Log, TEXT("URUIManager::GetCacheUIByClass->"));
    for (auto& Widgets : CacheUIMap)
    {
        UBaseWidget* const* FindShowWidget = Widgets.Value.UIs.FindByPredicate(
            [WidgetClass](const UBaseWidget* CompareWidget)
            {
                return CompareWidget->IsA(WidgetClass);
            });

        if (FindShowWidget)
            OutUIs.Add(*FindShowWidget);
    }
}

void URUIManager::CloseUI(UBaseWidget* UI)
{
    if (nullptr == UI) return;

    if (IsUiInCache(UI) == false) //不在缓存中，不属于UI管理范畴
        return;

    switch (UI->UIShowMode)
    {
    case EUIShowMode::Normal:
        if (OpeningUIArr.Find(UI) == INDEX_NONE)
            return;
        OpeningUIArr.Remove(UI);
        UI->Close();
        break;
    case EUIShowMode::ReverseChange:
        PopUIOutStack(UI);
        break;
    case EUIShowMode::HideOther:
        CloseUIAndShowOther(UI);
        break;
    default:
        break;
    }
    return;
}

EUILayer URUIManager::GetUILayerInBP(UBaseWidget* Widget)
{
    for (auto& Widgets : CacheUIMap)
    {
        if (Widgets.Value.UIs.Contains(Widget))
            return Widgets.Key;
    }
    return EUILayer::Base;
}

void URUIManager::CloseWidgetByClass(TSubclassOf<UBaseWidget> UserWidgetClass)
{
    if (nullptr == UserWidgetClass)
    {
        UE_LOG(LogTemp, Log, TEXT("CloseUserWidget->nullptr"));
        return;
    }
    UE_LOG(LogTemp, Log, TEXT("CloseUserWidget->%s"), *(UserWidgetClass->GetName()));
    TArray<UBaseWidget*> OutUIs;
    GetCacheUIByClassInBP(UserWidgetClass, OutUIs);
    for (auto Iter(OutUIs.CreateIterator()); Iter; Iter++)
    {
        CloseUI(*Iter);
    }
}

void URUIManager::CloseWidget(UBaseWidget* InWidget)
{
    CloseUI(InWidget);
}

void URUIManager::ShowUIAndHideOther(UBaseWidget* UI)
{
    //把“正在显示集合”与“栈集合”中所有窗体都隐藏。
    for (UBaseWidget* BaseUI : OpeningUIArr)
    {
        BaseUI->Hide();
    }
    for (UBaseWidget* BaseUI : MutexUIArr)
    {
        BaseUI->Hide();
    }

    if (OpeningUIArr.Find(UI) == INDEX_NONE)
        OpeningUIArr.Add(UI);
}

void URUIManager::CloseUIAndShowOther(UBaseWidget* UI)
{
    if (OpeningUIArr.Find(UI) == INDEX_NONE)
        return;

    //当前窗体隐藏状态，且“正在显示”集合中，移除本窗体
    OpeningUIArr.Remove(UI);
    UI->Close();

    //把“正在显示集合”中所有窗体都定义重新显示状态;模态栈里面将最后一个设为重新显示
    for (UBaseWidget* BaseUI : OpeningUIArr)
    {
        BaseUI->ReShow();
    }
    UBaseWidget* StaUI = MutexUIArr.Last();
    if (StaUI)
        StaUI->ReShow();
}

void URUIManager::AddOpeningUI(UBaseWidget* UI)
{
    if (UI && OpeningUIArr.Contains(UI) == false)
        OpeningUIArr.Add(UI);
}

void URUIManager::RemoveOpeningUI(UBaseWidget* UI)
{
    if (UI && OpeningUIArr.Contains(UI) == true)
        OpeningUIArr.Remove(UI);
}

void URUIManager::AddUIToCache(UBaseWidget* UI)
{

}

void URUIManager::RemoveUIFromCache(UBaseWidget* UI)
{

}

void URUIManager::PushUIToStack(UBaseWidget* UI)
{
    //判断“栈”集合中，是否有其他的窗体，有则隐藏处理。
    if (MutexUIArr.Num() > 0)
    {
        UBaseWidget* TopUIForm = MutexUIArr.Last();
        TopUIForm->Hide();
    }
    if (UI)
        MutexUIArr.Add(UI);
}

//出栈处理
void URUIManager::PopUIOutStack(UBaseWidget* UI)
{
    if (MutexUIArr.Num() >= 2)
    {
        UBaseWidget* TopUI = MutexUIArr.Last();
        if (UI != TopUI)
            return;
        
        MutexUIArr.RemoveAt(MutexUIArr.Num() - 1);
        TopUI->Close();

        UBaseWidget* NextUI = MutexUIArr.Last();
        NextUI->ReShow();
    }
    else if (MutexUIArr.Num() == 1)
    {
        UBaseWidget* TopUI = MutexUIArr.Last();
        if (UI != TopUI)
            return;
        
        TopUI->Close();
    }
}

void URUIManager::ClearStackArray()
{
    if (MutexUIArr.Num() > 0)
        MutexUIArr.Empty();    //清空栈集合
}

bool URUIManager::IsUiInCache(UBaseWidget* UI)
{
    bool bIsContain = false;
    for (auto& Widgets : CacheUIMap)
    {
        if( Widgets.Value.UIs.Contains(UI))
        {
            bIsContain = true;
            break;
        }
    }
    return bIsContain;
}

void URUIManager::DestoryAllUI(ULevel* InLevel, UWorld* InWorld)
{
    for (auto& Widgets : CacheUIMap)
    {
        for (UBaseWidget* Widget : Widgets.Value.UIs)
        {
            if (Widget && Widget->IsInViewport())
            {
                Widget->RemoveFromViewport();
                Widget->Close();
            }
        }
    }
    CacheUIMap.Reset();
}
