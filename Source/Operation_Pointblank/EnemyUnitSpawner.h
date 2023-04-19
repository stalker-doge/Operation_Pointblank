// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitSpawner.h"
#include "EnemyAI.h"
#include "EnemyUnitSpawner.generated.h"



UCLASS()
class OPERATION_POINTBLANK_API AEnemyUnitSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEnemyUnitSpawner();

	UPROPERTY(EditAnywhere, Category = "Units")
		TSubclassOf<AEnemyAI> EnemyAIBP;

	UFUNCTION(BlueprintCallable, Category = "Units")
		void SpawnEnemyUnit();
	
	UPROPERTY(EditAnywhere, Category = "UnitsSpawning")
		float TimeToSpawn = 2.f;

	FActorSpawnParameters SpawnParams;

	FTimerHandle OutHandle;

	UPROPERTY(EditAnywhere, Category = "Units")
		int _totalPoints;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
