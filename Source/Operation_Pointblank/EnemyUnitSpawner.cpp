// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyUnitSpawner.h"

AEnemyUnitSpawner::AEnemyUnitSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create a root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void AEnemyUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle OutHandle;
	//makes a timer that spawns units every 5 seconds
	GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &AEnemyUnitSpawner::SpawnEnemyUnit, TimeToSpawn, true);
}

void AEnemyUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyUnitSpawner::SpawnEnemyUnit()
{
	if (EnemyAIBP)
	{
		//AEnemyAI* UnitRef = GetWorld()->SpawnActor<AEnemyAI>(EnemyAIBP, GetTransform(), SpawnParams);
		//tries to spawn enemy units near point but tries to not overlap
		FVector SpawnLocation = GetActorLocation() + FMath::VRand() * 1000;
		FRotator SpawnRotation = GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		AEnemyAI* UnitRef = GetWorld()->SpawnActor<AEnemyAI>(EnemyAIBP, SpawnLocation, SpawnRotation, SpawnParams);
		UE_LOG(LogTemp, Warning, TEXT("Enemy Unit Spawned"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Unit Not Spawned"));
	}
}
