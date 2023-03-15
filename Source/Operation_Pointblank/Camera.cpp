// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACamera::ACamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create our components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//Attach our components
	StaticMeshComp->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(StaticMeshComp);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	//Assign SpringArm class variables.
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;
	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
	}
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

	//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
	CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	SpringArmComp->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);
	NewRotation = SpringArmComp->GetComponentRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
	SpringArmComp->SetWorldRotation(NewRotation);
	if (!MovementInput.IsZero())
	{
		//Scale our movement input axis values by 100 units per second
		MovementInput = MovementInput.GetSafeNormal() * 100.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}
}
//Input functions
void ACamera::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ACamera::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ACamera::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ACamera::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void ACamera::ZoomIn()
{
	bZoomingIn = true;
}

void ACamera::ZoomOut()
{
	bZoomingIn = false;
}

// Called to bind functionality to input
void ACamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Hook up events for "ZoomIn"
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &ACamera::ZoomOut);

	//Hook up every-frame handling for our four axes
	InputComponent->BindAxis("MoveForward", this, &ACamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACamera::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &ACamera::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &ACamera::YawCamera);

}

