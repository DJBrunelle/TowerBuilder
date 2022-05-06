// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerSpawner.h"

#include <random>

ATowerSpawner::ATowerSpawner()
{
}

void ATowerSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnTower();
}

void ATowerSpawner::SpawnTower()
{
	if(UWorld* World = GetWorld())
	{
		
		// Get Starting point relative to Spawner position
		const FVector StartVector = FVector(Radius, 0, 0);
		
		// Define Axis of rotation
		const FVector AxisOfRotation = FVector(0, 0, 1);

		// Determine circumference
		const float Circumference = 2 * std::_Pi * Radius;

		// Iterate starting at 3 cubes and see if it will fit, then try 4 cubes etc.
		bool CubesFit = true;
		int NumCubes = 3;
		while(CubesFit)
		{
			// Get bottom right corner of zeroth cube
			FVector RightCorner = StartVector + FVector(-CubeLength/2, CubeLength/2, 0);

			// Get next cube on point assuming NumCubes on circle
			const float FirstPt = Circumference / NumCubes;
			const float Angle = (FirstPt / Circumference) * 360;
			FVector PtLocation = StartVector.RotateAngleAxis(Angle, AxisOfRotation);
			//Get bottom left corner vector of next cube
			FVector LeftCorner = PtLocation + FRotator(0, Angle, 0).RotateVector(FVector(-CubeLength/2,-CubeLength/2,0));


			// Measure distance between corners of the 2 cubes
			// If Y coordinate of second cube is left of Y coord of first cube, they are overlapping
			if (FVector Diff = LeftCorner - RightCorner; Diff.Y < 0)
			{
				CubesFit = false;
			} else if (Diff.Length() > 5) // Distance between cubes must be at least 5 units
			{
				NumCubes++;
			} else // NumCubes doesn't fit
			{
				CubesFit = false;
			}
		}
		for (int ij = 0; ij < TowerHeight; ij++)
		{
			const float Offset = (360 * ((static_cast<float>(ij)/NumCubes))) / 2;
			// GEngine->AddOnScreenDebugMessage(-1,60.f,FColor::White,FString::Printf(TEXT("%f"), Offset));
			// Loop to spawn each cube around circle center
			for (int ii = 0; ii < NumCubes; ii++)
			{
				const float Angle = (360 * ((static_cast<float>(ii)/NumCubes))) + Offset;
				
				FVector NewLocation = GetTransform().GetLocation();

				const FVector RotateValue = StartVector.RotateAngleAxis(Angle, AxisOfRotation);

				NewLocation.X += RotateValue.X;
				NewLocation.Y += RotateValue.Y;
				NewLocation.Z += RotateValue.Z + (ij * CubeLength) + 1;

				FRotator NewRotation = FRotator(0, Angle, 0);

				World->SpawnActor<ABaseCube>(Cube, NewLocation, NewRotation);
			}
		}

		// Repeat loop increasing the layer height by 1 cube
	}
}
