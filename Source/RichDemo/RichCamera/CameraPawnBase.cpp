
#include "CameraPawnBase.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACameraPawnBase::ACameraPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	// Make the scene component the root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	//// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->FieldOfView = 90.0f;
	FollowCamera->bConstrainAspectRatio = true;
	FollowCamera->AspectRatio = 1.777778f;

	FollowCamera->PostProcessBlendWeight = 1.0f;

	FollowCamera->SetupAttachment(RootComponent); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void ACameraPawnBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACameraPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePawnRotation(DeltaTime);

}

// Called to bind functionality to input
void ACameraPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACameraPawnBase::BecomeViewTarget(class APlayerController* PC)
{
	Super::BecomeViewTarget(PC);
	FollowCamera->SetComponentTickEnabled(true);

}

/** Called when this actor is no longer the given PlayerController's ViewTarget. Also triggers the Blueprint event K2_OnEndViewTarget. */
void ACameraPawnBase::EndViewTarget(class APlayerController* PC)
{
	Super::EndViewTarget(PC);

	FollowCamera->SetComponentTickEnabled(false);

}


FRotator ACameraPawnBase::GetViewRotation() const
{
	if (auto PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		return PlayerController->GetControlRotation();
	}
	else
	{
		return FRotator::ZeroRotator;
	}
}

void ACameraPawnBase::SetViewRotation(const FRotator& Rot)
{

	if (auto PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		return PlayerController->SetControlRotation(Rot);
	}

}

void ACameraPawnBase::UpdatePawnRotation(float DeltaTime)
{
	if (auto PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		FRotator PCRotator = PlayerController->GetControlRotation();

		FRotator LimitRotator = FRotator(
			FMath::Clamp(PCRotator.Pitch, CameraFovSetting.ViewPitchMin, CameraFovSetting.ViewPitchMax),
			FMath::Clamp(PCRotator.Yaw, CameraFovSetting.ViewYawMin, CameraFovSetting.ViewYawMax),
			PCRotator.Roll
		);

		this->SetActorRotation(LimitRotator);
	}
}
