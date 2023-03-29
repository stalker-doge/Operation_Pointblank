// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitAI.h"

// Sets default values
AUnitAI::AUnitAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnitAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

