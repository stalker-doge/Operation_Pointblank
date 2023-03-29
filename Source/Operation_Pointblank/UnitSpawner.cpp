// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSpawner.h"

// Sets default values
AUnitSpawner::AUnitSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AUnitSpawner::SpawnUnit()
{
	if (UnitAIBP)
	{
		AUnitAI* UnitRef = GetWorld()->SpawnActor<AUnitAI>(UnitAIBP, GetTransform(), SpawnParams);
	}
}

// Called when the game starts or when spawned
void AUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle OutHandle;
	GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &AUnitSpawner::SpawnUnit, TimeToSpawn);
	
}

// Called every frame
void AUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

