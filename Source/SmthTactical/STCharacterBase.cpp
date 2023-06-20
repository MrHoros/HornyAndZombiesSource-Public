// Fill out your copyright notice in the Description page of Project Settings.


#include "STCharacterBase.h"

// Sets default values
ASTCharacterBase::ASTCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	RestoreStamina();
	
}

void ASTCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASTCharacterBase::ChangeStamina(int Value)
{
	Stamina += Value;
	Stamina = FMath::Clamp(Stamina, 0, MaxStamina);
	UE_LOG(LogTemp, Warning, TEXT("NEW STAMINA: %i, CHANGE VALUE: %i"), Stamina, Value);
	OnStaminaChanged.Broadcast(Stamina);
}

void ASTCharacterBase::RestoreStamina()
{
	Stamina = MaxStamina;
	OnStaminaChanged.Broadcast(Stamina);
}

float ASTCharacterBase::GetAttackRange()
{
	return AttackRange;
}

int ASTCharacterBase::GetDamage()
{
	return Damage;
}

int ASTCharacterBase::GetStamina()
{
	return Stamina;
}

int ASTCharacterBase::GetMaxStamina()
{
	return MaxStamina;
}

int ASTCharacterBase::GetTeamIndex()
{
	return TeamIndex;
}

FColor ASTCharacterBase::GetTeamColor()
{
	return TeamColor;
}

FString ASTCharacterBase::GetTeamName()
{
	return TeamName;
}

FString ASTCharacterBase::GetUnitName()
{
	return UnitName;
}

int ASTCharacterBase::GetModPoints()
{
	return ModPoints;
}

int ASTCharacterBase::GetAttackChanceBoost()
{
	return AttackChanceBoost;
}

int ASTCharacterBase::GetDefenseChanceBoost()
{
	return DefenseChanceBoost;
}

void ASTCharacterBase::SetModPoints(int Value)
{
	ModPoints = Value;
}

void ASTCharacterBase::SetAttackChanceBoost(int Value)
{
	AttackChanceBoost = Value;
}

void ASTCharacterBase::SetDefenseChanceBoost(int Value)
{
	DefenseChanceBoost = Value;
}

void ASTCharacterBase::ChangeModPoints(int Value)
{
	ModPoints += Value;
	ModPoints = FMath::Clamp(ModPoints, 0, 100);
}

void ASTCharacterBase::ChangeAttackChanceBoost(int Value)
{
	AttackChanceBoost += Value;
	AttackChanceBoost = FMath::Clamp(AttackChanceBoost, 0, 100);
}

void ASTCharacterBase::ChangeDefenseChanceBoost(int Value)
{
	DefenseChanceBoost += Value;
	DefenseChanceBoost = FMath::Clamp(DefenseChanceBoost, 0, 100);
}

int ASTCharacterBase::GetDefenseChance()
{
	return FMath::Clamp(BaseDefenseChance + DefenseChanceBoost, 0, 100);
}

int ASTCharacterBase::CalculateBoostFromModPoints()
{
	int additionalChance = 0;
	for (int i = 0; i < ModPoints; i++)
	{
		additionalChance += FMath::Clamp((10 - (2 * i)), 2, 100);
	}
	return additionalChance;
}

void ASTCharacterBase::ConvertModPointsToDefenseChanceBoost()
{

	DefenseChanceBoost += CalculateBoostFromModPoints();
	DefenseChanceBoost = FMath::Clamp(DefenseChanceBoost, 0, 100);
	ModPoints = 0;
}

void ASTCharacterBase::ConvertModPointsToAttackChanceBoost()
{
	AttackChanceBoost += CalculateBoostFromModPoints();
	AttackChanceBoost = FMath::Clamp(AttackChanceBoost, 0, 100);
	ModPoints = 0;
}

void ASTCharacterBase::ConvertStaminaToModPoints()
{
	ModPoints = Stamina;
	ModPoints = FMath::Clamp(ModPoints, 0, 100);
	Stamina = 0;
}

void ASTCharacterBase::AssignBaseDefenseChance()
{
	BaseDefenseChance = BaseDefenseChancePerStamina * MaxStamina;
}

UTexture* ASTCharacterBase::GetUnitIcon()
{
	return UnitIcon;
}

int ASTCharacterBase::GetChanceToAttackCharacter(ASTCharacterBase* Defender)
{
	int ChanceToAttack = 100 - Defender->GetDefenseChance() + GetAttackChanceBoost();
	ChanceToAttack = FMath::Clamp(ChanceToAttack, 0, 100);

	return ChanceToAttack;
}