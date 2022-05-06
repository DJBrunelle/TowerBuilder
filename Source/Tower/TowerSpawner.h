// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCube.h"
#include "Engine/TargetPoint.h"
#include "TowerSpawner.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_API ATowerSpawner : public ATargetPoint
{
	GENERATED_BODY()

public:
	ATowerSpawner();

	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Tower")
	TSubclassOf<ABaseCube> Cube;
	
private:

	UPROPERTY(EditAnywhere, Category="Tower")
	float Radius = 500;
	
	UPROPERTY(EditAnywhere, Category="Tower")
	int TowerHeight = 1;
	
	UPROPERTY(EditAnywhere, Category="Tower")
	int CubeLength = 100;

	

	void SpawnTower();
};
