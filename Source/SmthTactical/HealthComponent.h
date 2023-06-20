// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SMTHTACTICAL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

private:
	float Health;
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UFUNCTION(BlueprintPure)
	float GetHealth();

	UFUNCTION(BlueprintPure)
	float GetMaxHealth();

	UFUNCTION(BlueprintPure)
	float GetMissingHealth();

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);


	class ASmthTacticalGameModeBase* STGameMode;

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void SetHealth(float Value);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void ChangeHealth(float Value);
	
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void RestoreHealth();
};
