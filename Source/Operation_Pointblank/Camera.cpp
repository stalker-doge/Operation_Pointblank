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
	SpringArmComp->TargetArmLength = 100.f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;
	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	_speed = 10;
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
	//Move the camera based on the input
	FVector ForwardMovement = GetActorForwardVector() * MovementInput.X*_speed;
	FVector RightMovement = GetActorRightVector() * MovementInput.Y * _speed;
	AddActorWorldOffset((ForwardMovement + RightMovement) * 100.0f * DeltaTime, true);
	//Zoom the camera based on the input
	SpringArmComp->TargetArmLength += ZoomFactor;
	//Clamp the camera zoom
	SpringArmComp->TargetArmLength = FMath::Clamp(SpringArmComp->TargetArmLength, 100.0f, 400.0f);
	//Rotate the camera based on the input
	AddActorLocalRotation(FRotator(CameraInput.Y, CameraInput.X, 0.0f));
	
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
	ZoomFactor = -100.0f;
}

void ACamera::ZoomOut()
{
	bZoomingIn = false;
	ZoomFactor = 100.0f;
}

void ACamera::Zoom(float AxisValue)
{
	if (AxisValue > 0.0f)
	{
		ZoomIn();
	}
	else if (AxisValue < 0.0f)
	{
		ZoomOut();
	}
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
	InputComponent->BindAxis("LookUp", this, &ACamera::PitchCamera);
	InputComponent->BindAxis("Turn", this, &ACamera::YawCamera);
	InputComponent->BindAxis("Zoom", this, &ACamera::Zoom);
	
}

