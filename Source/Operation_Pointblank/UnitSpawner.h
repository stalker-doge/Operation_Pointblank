// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitAI.h"
#include "UnitSpawner.generated.h"

UCLASS()
class OPERATION_POINTBLANK_API AUnitSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitSpawner();

	UPROPERTY(EditDefaultsOnly, Category = "Units")
		TSubclassOf<AUnitAI> UnitAIBP;

	UPROPERTY(EditDefaultsOnly, Category = "UnitsSpawning")
		float TimeToSpawn = 2.f;

	FActorSpawnParameters SpawnParams;

	UFUNCTION()
	void SpawnUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
