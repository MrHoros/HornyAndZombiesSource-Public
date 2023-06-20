// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStaminaChangedDelegate, int, NewStamina);

UCLASS()
class SMTHTACTICAL_API ASTCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASTCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	int GetTeamIndex();

	UFUNCTION(BlueprintPure)
	FString GetTeamName();

	UFUNCTION(BlueprintPure)
	int GetMaxStamina();

	UFUNCTION(BlueprintPure)
	int GetStamina();

	UFUNCTION(BlueprintPure)
	int GetDamage();

	UFUNCTION(BlueprintPure)
	float GetAttackRange();

	UFUNCTION(BlueprintPure)
	FColor GetTeamColor();

	UFUNCTION(BlueprintPure)
	FString GetUnitName();

	UFUNCTION(BlueprintPure)
	int GetModPoints();

	UFUNCTION(BlueprintPure)
	int GetAttackChanceBoost();

	UFUNCTION(BlueprintPure)
	int GetDefenseChanceBoost();

	UFUNCTION(BlueprintPure)
	int GetDefenseChance();

	UFUNCTION(BlueprintPure)
	UTexture *GetUnitIcon();

	UFUNCTION(BlueprintPure)
	int GetChanceToAttackCharacter(ASTCharacterBase* Defender);

private:
	int BaseDefenseChance = 0;
	int AttackChanceBoost = 0;
	int DefenseChanceBoost = 0;
	int Stamina = 0;

	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int MaxStamina = 0;

	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int Damage = 0;

	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int BaseDefenseChancePerStamina = 5;

	UPROPERTY(EditAnywhere, Category = "Team", meta = (AllowPrivateAccess = "true"))
	int TeamIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int ModPoints = 0;

	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 0;

	UPROPERTY(EditAnywhere, Category = "Team", meta = (AllowPrivateAccess = "true"))
	FColor TeamColor = FColor(0, 0, 0);

	UPROPERTY(EditAnywhere, Category = "Team", meta = (AllowPrivateAccess = "true"))
	FString TeamName = TEXT("");

	UPROPERTY(EditAnywhere, Category = "General", meta = (AllowPrivateAccess = "true"))
	FString UnitName = TEXT("");

	UPROPERTY(EditAnywhere, Category = "General", meta = (AllowPrivateAccess = "true"))
	UTexture* UnitIcon = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "General", meta = (AllowPrivateAccess = "true"))
	FStaminaChangedDelegate OnStaminaChanged;


	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void SetModPoints(int Value);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void SetAttackChanceBoost(int Value);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void SetDefenseChanceBoost(int Value);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void ChangeModPoints(int Value);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void ChangeAttackChanceBoost(int Value);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void ChangeDefenseChanceBoost(int Value);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	int CalculateBoostFromModPoints();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void ConvertStaminaToModPoints();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void ConvertModPointsToAttackChanceBoost();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void ConvertModPointsToDefenseChanceBoost();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void AssignBaseDefenseChance();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void ChangeStamina(int Value);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void RestoreStamina();
};
