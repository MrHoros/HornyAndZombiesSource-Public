// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterSpawnerComponent.generated.h"

class ASTCharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SMTHTACTICAL_API UCharacterSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterSpawnerComponent();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	ASTCharacterBase* SpawnCharacterAtLocation(TSubclassOf<ASTCharacterBase> CharacterToSpawn, FVector Location);
};
