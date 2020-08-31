// Fill out your copyright notice in the Description page of Project Settings.


#include "WG_MainMenu.h"
#include "EventDispatcher.h"

void UWG_MainMenu::OnMenuButtonClick(EMainMenuType Parm)
{
	if (GEventDispatcher.OnMainMenuClicked.IsBound())
	{
		GEventDispatcher.OnMainMenuClicked.Broadcast(Parm);
	}
}