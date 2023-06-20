// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SmthTacticalGameModeBase.generated.h"


UENUM(BlueprintType)
enum class EPhase : uint8
{
	PE_None UMETA(DisplayName = "None"),
	PE_Init UMETA(DisplayName = "Init"),
	PE_Setup UMETA(DisplayName = "Setup"),
	PE_Move UMETA(DisplayName = "Move"),
	PE_Attack UMETA(DisplayName = "Attack"),
	PE_TurnEnd UMETA(DisplayName = "TurnEnd"),
	PE_LevelEnd UMETA(DisplayName = "LevelEnd")
};

UCLASS()
class SMTHTACTICAL_API ASmthTacticalGameModeBase : public AGameMode
{
	GENERATED_BODY()
	

public:
	void ActorDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterDied();
	UFUNCTION(BlueprintImplementableEvent)
	void OnPhaseChanged(EPhase OldPhase);


private:
	EPhase CurrentPhase = EPhase::PE_None;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int WinnerTeamIndex = -1;

	UFUNCTION(BlueprintPure, meta = (AllowPrivateAccess = "true"))
	int32 GetAllCharactersCount() const;

	UFUNCTION(BlueprintPure, meta = (AllowPrivateAccess = "true"))
	int32 GetCharactersCountOfTeam(FString Team) const;

	UFUNCTION(BlueprintPure, meta = (AllowPrivateAccess = "true"))
	TArray <AActor*> GetSortedCharactersByMaxStamina(TArray<AActor*> Characters) const;

	UFUNCTION(BlueprintPure, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> GetAllCharacters() const;

	UFUNCTION(BlueprintPure, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> GetCharactersOfTeam(FString Team) const;

	UFUNCTION(BlueprintPure, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> GetCharactersOfTeamIndex(int TeamIndex) const;

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> CreateCharactersPriorityQueue(TArray<AActor*> TeamA, TArray<AActor*> TeamB);

	UFUNCTION(BlueprintPure, meta = (AllowPrivateAccess = "true"))
	EPhase GetCurrentPhase() const;

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void SetCurrentPhase(EPhase NewPhase);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void NextPhase();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))

	AActor* GetClosestCharacterOfTeamIndex(int TeamIndex, FVector Location);
};
