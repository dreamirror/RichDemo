// Fill out your copyright notice in the Description page of Project Settings.


#include "WG_Start.h"
#include "MoviePlayer.h"

void UWG_Start::OnClickUnlock()
{
	GetMoviePlayer()->StopMovie();
}

bool UWG_Start::UnlockBtnVisible()
{
	return GetMoviePlayer()->IsLoadingFinished();
}