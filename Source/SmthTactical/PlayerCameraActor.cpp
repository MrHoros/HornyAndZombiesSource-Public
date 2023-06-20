// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraActor.h"

// Sets default values
APlayerCameraActor::APlayerCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
FVector APlayerCameraActor::ClampLocation(FVector NewLocation)
{
	FVector clampedLocation = NewLocation;
	float maxY = BaseLocation.Y + YBorderOffset;
	float minY = BaseLocation.Y - YBorderOffset;
	float maxX = BaseLocation.X + XBorderOffset;
	float minX = BaseLocation.X - XBorderOffset;

	if (clampedLocation.Y > maxY)
	{
		clampedLocation.Y = maxY;
	}
	else if (clampedLocation.Y < minY)
	{
		clampedLocation.Y = minY;
	}

	if (clampedLocation.X > maxX)
	{
		clampedLocation.X = maxX;
	}
	else if (clampedLocation.X < minX)
	{
		clampedLocation.X = minX;
	}

	return clampedLocation;
}

void APlayerCameraActor::SetBaseLocation(FVector NewLocation)
{
	BaseLocation = NewLocation;
}

FVector APlayerCameraActor::GetBaseLocation()
{
	return BaseLocation;
}