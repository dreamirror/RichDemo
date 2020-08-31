// Fill out your copyright notice in the Description page of Project Settings.


#include "RGameInstance.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"

#include "RUIManager.h"
#include "RMaskManager.h"
#include "RichActorManager/RichActorManager.h"
#include "Blueprint/UserWidget.h"


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

	FRichActorManager::CreateSingleton();

}


void URGameInstance::Shutdown()
{
	Super::Shutdown();
	
	MOUIManager->Shutdown();
	MaskManager->Shutdown();

	FRichActorManager::DestroySingleton();

	Instance = nullptr;
}


void URGameInstance::BeginLoadingScreen(const FString& MapName)
{
	UE_LOG(LogTemp, Log, TEXT("URGameInstance::BeginLoadingScreen------------->"));
	FLoadingScreenAttributes LoadingScreen;
	TSubclassOf<UUserWidget> WidgetClass;
	if (bFirstLoading)
	{
		WidgetClass = LoadClass<UUserWidget>(NULL, TEXT("/Game/UMG/WB_Start.WB_Start_C"));
		LoadingScreen.bWaitForManualStop = true;
		LoadingScreen.bMoviesAreSkippable = true;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
	}
	else
	{
		WidgetClass = LoadClass<UUserWidget>(NULL, TEXT("/Game/UMG/WB_Loading.WB_Loading_C"));
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
	}

	TSharedPtr<SWidget> WidgetPtr = CreateWidget<UUserWidget>(this, WidgetClass)->TakeWidget();

	LoadingScreen.MoviePaths.Add(TEXT("LoadingScreen"));
	LoadingScreen.WidgetLoadingScreen = WidgetPtr;
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

void URGameInstance::EndLoadingScreen(UWorld* LoadedWorld)
{

	UE_LOG(LogTemp, Log, TEXT("URGameInstance::EndLoadingScreen------------->"));
	if (!IsRunningDedicatedServer())
	{

	}
}
