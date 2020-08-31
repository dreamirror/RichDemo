﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawnBase.generated.h"

/**
 * 相机基础类型，继承于pawn,可以使用AI驱动，且不直接使用CameraActor方便之后的漫游模式绑定到Character身上
 */
UCLASS()
class ACameraPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawnBase();

	virtual FRotator GetViewRotation() const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetViewRotation(const FRotator& Rot);
	virtual void UpdatePawnLocation(float DeltaTime){};
	virtual void UpdatePawnRotation(float DeltaTime);

	/** Called when this actor becomes the given PlayerController's ViewTarget. Triggers the Blueprint event K2_OnBecomeViewTarget. */
	virtual void BecomeViewTarget(class APlayerController* PC) override;

	/** Called when this actor is no longer the given PlayerController's ViewTarget. Also triggers the Blueprint event K2_OnEndViewTarget. */
	virtual void EndViewTarget(class APlayerController* PC) override;

public:

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

protected:

};