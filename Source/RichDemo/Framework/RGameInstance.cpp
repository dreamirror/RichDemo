// Fill out your copyright notice in the Description page of Project Settings.


#include "RGameInstance.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "RMaskManager.h"


URGameInstance* URGameInstance::Instance = nullptr;

void URGameInstance::OnStart()
{
	Super::OnStart();
}

//------------------------------------------------------------------------------------------------------------------------------------------
void URGameInstance::Init()
{
	Super::Init();
	Instance = this;

	//绑定关卡加载时的委托回调
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &URGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &URGameInstance::EndLoadingScreen);

	//初始化UI管理器
	MOUIManager = NewObject<URUIManager>(this, URUIManager::StaticClass());
	MOUIManager->Init(GetWorld());

	MaskManager = NewObject<URMaskManager>(this, URMaskManager::StaticClass());
	URMaskManager::Get()->InitMask(GetWorld());

}


void URGameInstance::Shutdown()
{
	Super::Shutdown();
	
	MOUIManager->Shutdown();
	MaskManager->Shutdown();

	Instance = nullptr;
}


void URGameInstance::BeginLoadingScreen(const FString& MapName)
{
	//UE_LOG(LogTemp, Log, TEXT("URGameInstance::BeginLoadingScreen------------->"));
	//if (!IsRunningDedicatedServer())
	//{

	//	FLoadingScreenAttributes LoadingScreen;
	//	//LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
	//	//LoadingScreen.bMoviesAreSkippable = true;
	//	//LoadingScreen.bWaitForManualStop = true;
	//	//LoadingScreen.PlaybackType = EMoviePlaybackType::MT_Looped;
	//	//引擎默认Widget
	//	//LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	//	//自定义Widget
	//	LoadingWidget = GetUIManager()->LoadUserWidget<UWG_Loading>();
	//	if (LoadingWidget) {
	//		TSharedPtr<SWidget> WidgetPtr = LoadingWidget->TakeWidget();
	//		LoadingScreen.WidgetLoadingScreen = WidgetPtr;
	//	}

	//	//播放视频，视频文件需要放在Content\Movies下
	//	//LoadingScreen.MoviePaths.Add("squad_intro_movie");
	//	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	//}
}

void URGameInstance::EndLoadingScreen(UWorld* LoadedWorld)
{

	UE_LOG(LogTemp, Log, TEXT("URGameInstance::EndLoadingScreen------------->"));
	if (!IsRunningDedicatedServer())
	{

	}
}
