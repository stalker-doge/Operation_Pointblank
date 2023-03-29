// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyUnitSpawner.h"

AEnemyUnitSpawner::AEnemyUnitSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyUnitSpawner::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyUnitSpawner::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	FTimerHandle OutHandle;
	GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &AEnemyUnitSpawner::SpawnEnemyUnit, TimeToSpawn);
}

void AEnemyUnitSpawner::SpawnEnemyUnit()
{
	if (EnemyAIBP)
	{
		AEnemyAI* UnitRef = GetWorld()->SpawnActor<AEnemyAI>(UnitAIBP, GetTransform(), SpawnParams);
	}
}
