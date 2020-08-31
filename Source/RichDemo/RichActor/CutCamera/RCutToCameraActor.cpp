// Fill out your copyright notice in the Description page of Project Settings.
#include "RCutToCameraActor.h"
#include "DrawDebugHelpers.h"
#include "Misc/QualifiedFrameTime.h"

#include "Framework/RichActorManager/RichActorManager.h"
#include "RichCamera/CameraPawnBase.h"

// Sets default values
ARCutToCameraActor::ARCutToCameraActor()
{

}

ARCutToCameraActor::~ARCutToCameraActor()
{

}

void ARCutToCameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARCutToCameraActor::Init()
{
	Super::Init();
}

void ARCutToCameraActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
#if WITH_EDITOR

#endif
}

void ARCutToCameraActor::OnActive()
{
	Super::OnActive();
}

void ARCutToCameraActor::OnDisActive()
{
	Super::OnDisActive();
}

