// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCube.h"

// Sets default values
ABaseCube::ABaseCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SceneTransform = CreateDefaultSubobject<USceneComponent>("Scene");

	RootComponent = SceneTransform;
	CubeMesh->SetupAttachment(SceneTransform);

	CubeMesh->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void ABaseCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

