// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyUnitSpawner.h"

AEnemyUnitSpawner::AEnemyUnitSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create a root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	_totalPoints = 50;
}

void AEnemyUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	//makes a timer that spawns units every 5 seconds
	GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &AEnemyUnitSpawner::SpawnEnemyUnit, TimeToSpawn, true);
}

void AEnemyUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_totalPoints <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(OutHandle);
	}
}

void AEnemyUnitSpawner::SpawnEnemyUnit()
{
	//if (EnemyAIBP)
	//{
	//	FVector SpawnLocation = GetActorLocation() + FMath::VRand() * 50;
	//	FRotator SpawnRotation = GetActorRotation();
	//	SpawnParams.Owner = this;
	//	AEnemyAI* UnitRef = GetWorld()->SpawnActor<AEnemyAI>(EnemyAIBP, SpawnLocation, SpawnRotation, SpawnParams);
	//	_totalPoints = _totalPoints - UnitRef->_pointCost;
	//	UE_LOG(LogTemp, Warning, TEXT("Enemy Unit Spawned"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Enemy Unit Not Spawned"));
	//}

	
	if (_totalPoints >= 30)
	{
		if (EnemyAIBPTier2)
		{
			FVector SpawnLocation = GetActorLocation() + FMath::VRand() * 50;
			FRotator SpawnRotation = GetActorRotation();
			SpawnParams.Owner = this;
			AEnemyAI* UnitRef = GetWorld()->SpawnActor<AEnemyAI>(EnemyAIBPTier2, SpawnLocation, SpawnRotation, SpawnParams);
			_totalPoints = _totalPoints - UnitRef->_pointCost;
			UE_LOG(LogTemp, Warning, TEXT("Enemy Unit Spawned"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Enemy Unit Not Spawned"));
		}
	}
	else if (_totalPoints >= 0 && _totalPoints < 30)
	{
		if (EnemyAIBP)
		{
			FVector SpawnLocation = GetActorLocation() + FMath::VRand() * 50;
			FRotator SpawnRotation = GetActorRotation();
			SpawnParams.Owner = this;
			AEnemyAI* UnitRef = GetWorld()->SpawnActor<AEnemyAI>(EnemyAIBP, SpawnLocation, SpawnRotation, SpawnParams);
			_totalPoints = _totalPoints - UnitRef->_pointCost;
			UE_LOG(LogTemp, Warning, TEXT("Enemy Unit Spawned"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Enemy Unit Not Spawned"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Unit Not Spawned"));
	}

}
