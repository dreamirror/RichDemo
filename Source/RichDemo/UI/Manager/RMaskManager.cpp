
#include "RMaskManager.h"
#include "Kismet/GameplayStatics.h"
#include "RGameInstance.h"
#include "Blueprint/UserWidget.h"


void URMaskManager::Shutdown()
{
	CancelMaskLayer();
	if (MaskPanel)
	{
		MaskPanel = nullptr;
	}
	bInit = false;
}

void URMaskManager::InitMask(UWorld* world)
{
	//init widget
	if (MaskUI.IsEmpty())
		return;

	if (MaskPanel)
	{
		return;
	}

	TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(NULL, *MaskUI);
	MaskPanel = CreateWidget<UUserWidget>(world, WidgetClass);

	if (MaskPanel)
	{
		MaskPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

URMaskManager * URMaskManager::Get()
{
	return URGameInstance::Get()->GetMaskManager();
}

void URMaskManager::SetMaskLayer(int32 Layer)
{
	if (Layer == 0 )
	{
		PreLayer = 0;
		CurLayer = 0;
		CancelMaskLayer();
		return;
	}

	if (Layer == CurLayer)
	{
		return;
	}

	if (MaskPanel)
	{
		if (MaskPanel->IsInViewport())
		{
			MaskPanel->RemoveFromParent();
		}

		PreLayer = CurLayer;
		CurLayer = Layer;
	
		UWorld* World = GetWorld();
		if (World && World->IsGameWorld())
		{
			if (UGameViewportClient* ViewportClient = World->GetGameViewport())
			{
				ViewportClient->AddViewportWidgetContent(MaskPanel->TakeWidget(), Layer);
				MaskPanel->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void URMaskManager::RevertMaskLayer()
{
	if (MaskPanel)
	{
		UWorld* World = GetWorld();
		if (World && World->IsGameWorld())
		{
			if (UGameViewportClient* ViewportClient = World->GetGameViewport())
			{
				ViewportClient->RemoveViewportWidgetContent(MaskPanel->TakeWidget());
				MaskPanel->SetVisibility(ESlateVisibility::Visible);
			}
		}
		SetMaskLayer(PreLayer);
	}
}

void URMaskManager::CancelMaskLayer()
{
	if (MaskPanel)
	{
		MaskPanel->SetVisibility(ESlateVisibility::Collapsed);
		//MaskPanel->RemoveFromParent();
		UWorld* World = GetWorld();
		if (World && World->IsGameWorld())
		{
			if (UGameViewportClient* ViewportClient = World->GetGameViewport())
			{
				ViewportClient->RemoveViewportWidgetContent(MaskPanel->TakeWidget());
				MaskPanel->SetVisibility(ESlateVisibility::Visible);
			}
		}
		CurLayer = 0;
	}
}