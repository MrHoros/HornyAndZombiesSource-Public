// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSpawnerComponent.h"
#include "STCharacterBase.h"

// Sets default values for this component's properties
UCharacterSpawnerComponent::UCharacterSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ASTCharacterBase* UCharacterSpawnerComponent::SpawnCharacterAtLocation(TSubclassOf<ASTCharacterBase> CharacterToSpawn, FVector Location)
{
	FRotator RandomRotator = FRotator::MakeFromEuler(FVector(0, 0, FMath::RandRange(0, 360)));
	ASTCharacterBase* NewCharacter = GetWorld()->SpawnActor<ASTCharacterBase>(CharacterToSpawn, Location, RandomRotator);

	return NewCharacter;
}
