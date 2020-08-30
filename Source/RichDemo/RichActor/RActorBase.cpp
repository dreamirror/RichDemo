// Fill out your copyright notice in the Description page of Project Settings.
#include "RActorBase.h"
#include "DrawDebugHelpers.h"
#include "Misc/QualifiedFrameTime.h"

#include "Framework/RichActorManager/RichActorManager.h"

// Sets default values
ARActorBase::ARActorBase()
{

}

ARActorBase::~ARActorBase()
{

}

void ARActorBase::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void ARActorBase::Init()
{
	
}

void ARActorBase::RegistIntoManager()
{
	if (FRichActorManager::IsSingletonExist())
		FRichActorManager::Singleton().RegistRichActor(this);
}

void ARActorBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
#if WITH_EDITOR

#endif
}

void ARActorBase::OnActive()
{
	BP_OnActive();
}

void ARActorBase::OnDisActive()
{
	BP_OnDisActive();
}

#if WITH_EDITOR
bool ARActorBase::ShouldTickIfViewportsOnly() const
{
	return WITH_EDITOR;
}
#endif
