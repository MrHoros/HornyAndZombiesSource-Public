#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "SmthTacticalGameModeBase.h"
#include "STCharacterBase.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	STGameMode = Cast<ASmthTacticalGameModeBase>(UGameplayStatics::GetGameMode(this));
	
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	//if (Damage <= 0.f) return;
	if (DamageCauser == GetOwner()) return;
	if (DamageCauser == DamagedActor) return;

	ASTCharacterBase* CharDamager = Cast<ASTCharacterBase>(DamageCauser);
	ASTCharacterBase* CharDamaged = Cast<ASTCharacterBase>(DamagedActor);

	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("HEALTH: %f"), Health);

	if (Health <= 0.f && STGameMode)
	{
		STGameMode->ActorDied(DamagedActor);
	}
}

float UHealthComponent::GetHealth()
{
	return Health;
}

void UHealthComponent::RestoreHealth()
{
	Health = MaxHealth;
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

float UHealthComponent::GetMissingHealth()
{
	return MaxHealth - Health;
}

void UHealthComponent::SetHealth(float Value)
{
	Health = Value;
}

void UHealthComponent::ChangeHealth(float Value)
{
	Health += Value;
}