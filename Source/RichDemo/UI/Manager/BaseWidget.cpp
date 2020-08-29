// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"
#include "RMaskManager.h"

void UBaseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    BindUIComponent();
}

void UBaseWidget::NativeDestruct()
{
    Super::NativeDestruct();
    UE_LOG(LogTemp, Log, TEXT("UBaseWidget::NativeDestruct------------->"));
}

void UBaseWidget::Show()
{
    this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    if (bShowMask)
        URMaskManager::Get()->SetMaskLayer(ZOrder);
    OnShow();
}

void UBaseWidget::ReShow()
{
    this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    if (bShowMask)
        URMaskManager::Get()->SetMaskLayer(ZOrder);
    OnReShow();
}

void UBaseWidget::Hide()
{
    this->SetVisibility(ESlateVisibility::Hidden);
    if (bShowMask)
        URMaskManager::Get()->CancelMaskLayer();
    OnHide();
}

void UBaseWidget::Close()
{
    this->SetVisibility(ESlateVisibility::Collapsed);
    if (bShowMask)
        URMaskManager::Get()->CancelMaskLayer();
    OnClose();

    if (OnUICloseCallBack.IsBound())
        OnUICloseCallBack.Broadcast();
}

void UBaseWidget::BindUIComponent()
{
}

void UBaseWidget::DoShowAnimation()
{
}

void UBaseWidget::DoCloseAnimation()
{
}
