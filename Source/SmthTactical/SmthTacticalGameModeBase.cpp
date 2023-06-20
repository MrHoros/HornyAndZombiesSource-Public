// Copyright Epic Games, Inc. All Rights Reserved.

#include "SmthTacticalGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "STCharacterBase.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"

void ASmthTacticalGameModeBase::ActorDied(AActor* DeadActor)
{
	if (ASTCharacterBase* DeadCharacter = Cast<ASTCharacterBase>(DeadActor))
	{
		//DeadCharacter->Destroy();
		OnCharacterDied();
	}
}

TArray<AActor*> ASmthTacticalGameModeBase::GetAllCharacters() const
{
	TArray<AActor*> AllCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASTCharacterBase::StaticClass(), AllCharacters);
	return AllCharacters;
}

TArray<AActor*> ASmthTacticalGameModeBase::GetCharactersOfTeam(FString Team) const
{
	TArray<AActor*> AllCharacters = GetAllCharacters();
	TArray<AActor*> TeamCharacters;
	for (AActor* Character : AllCharacters)
	{
		if (ASTCharacterBase* CharacterBase = Cast<ASTCharacterBase>(Character))
		{
			if (CharacterBase->GetTeamName() == Team)
			{
				TeamCharacters.Add(Character);
			}
		}
	}
	return TeamCharacters;
}

TArray<AActor*> ASmthTacticalGameModeBase::GetCharactersOfTeamIndex(int TeamIndex) const
{
	TArray<AActor*> AllCharacters = GetAllCharacters();
	TArray<AActor*> TeamCharacters;
	for (AActor* Character : AllCharacters)
	{
		if (ASTCharacterBase* CharacterBase = Cast<ASTCharacterBase>(Character))
		{
			if (CharacterBase->GetTeamIndex() == TeamIndex)
			{
				TeamCharacters.Add(Character);
			}
		}
	}
	return TeamCharacters;
}

int32 ASmthTacticalGameModeBase::GetAllCharactersCount() const
{
	TArray<AActor*> AllCharacters = GetAllCharacters();
	return AllCharacters.Num();
}

int32 ASmthTacticalGameModeBase::GetCharactersCountOfTeam(FString Team) const
{
	TArray<AActor*> TeamCharacters = GetCharactersOfTeam(Team);
	return TeamCharacters.Num();
}

TArray<AActor*> ASmthTacticalGameModeBase::GetSortedCharactersByMaxStamina(TArray<AActor*> Characters) const
{
	Characters.Sort([]( AActor& A, AActor& B)
		{
			if (ASTCharacterBase* CharacterA = Cast<ASTCharacterBase>(&A))
			{
				if (ASTCharacterBase* CharacterB = Cast<ASTCharacterBase>(&B))
				{
				return CharacterA->GetMaxStamina() > CharacterB->GetMaxStamina();
			}
		}
		return false;
	});
	return Characters;
}

EPhase ASmthTacticalGameModeBase::GetCurrentPhase() const
{
	return CurrentPhase;
}

void ASmthTacticalGameModeBase::SetCurrentPhase(EPhase NewPhase)
{
	EPhase OldPhase = CurrentPhase;
	CurrentPhase = NewPhase;
	OnPhaseChanged(OldPhase);
}



TArray<AActor*> ASmthTacticalGameModeBase::CreateCharactersPriorityQueue(TArray<AActor*> TeamA, TArray<AActor*> TeamB)
{
	TArray<AActor*> SortedTeamA = GetSortedCharactersByMaxStamina(TeamA);
	TArray<AActor*> SortedTeamB = GetSortedCharactersByMaxStamina(TeamB);
	TArray<AActor*> CharactersPriorityQueue;
	for (int i = 0; i < SortedTeamA.Num() || i < SortedTeamB.Num(); i++)
	{
		if (i < SortedTeamA.Num())
		{
			CharactersPriorityQueue.Add(SortedTeamA[i]);
		}
		if (i < SortedTeamB.Num())
		{
			CharactersPriorityQueue.Add(SortedTeamB[i]);
		}
	}
	return CharactersPriorityQueue;
}

void ASmthTacticalGameModeBase::NextPhase()
{
	switch (CurrentPhase)
	{
	case EPhase::PE_Init:
		SetCurrentPhase(EPhase::PE_Setup);
		break;
	case EPhase::PE_Setup:
		SetCurrentPhase(EPhase::PE_Move);
		break;
	case EPhase::PE_Move:
		SetCurrentPhase(EPhase::PE_Attack);
		break;
	case EPhase::PE_Attack:
		SetCurrentPhase(EPhase::PE_TurnEnd);
		break;
	case EPhase::PE_TurnEnd:
		TArray<AActor*> AlLCharacters = GetAllCharacters();
		bool bIsOnlyOneTeam = true;
		int TeamIndexToCheck = Cast<ASTCharacterBase>(AlLCharacters[0])->GetTeamIndex();

		for (AActor* Character : AlLCharacters)
		{
			if (ASTCharacterBase* CharacterBase = Cast<ASTCharacterBase>(Character))
			{
				if (CharacterBase->GetTeamIndex() != TeamIndexToCheck)
				{
					bIsOnlyOneTeam = false;
					break;
				}
			}
		}
		if (bIsOnlyOneTeam)
		{
			WinnerTeamIndex = TeamIndexToCheck;
			SetCurrentPhase(EPhase::PE_LevelEnd);
		}
		else
		{
			SetCurrentPhase(EPhase::PE_Move);
		}
		break;
	}
}

AActor* ASmthTacticalGameModeBase::GetClosestCharacterOfTeamIndex(int TeamIndex, FVector Location)
{
	TArray<AActor*> TeamCharacters = GetCharactersOfTeamIndex(TeamIndex);
	AActor* ClosestCharacter = nullptr;
	float ClosestDistance = 0;
	for (AActor* Character : TeamCharacters)
	{
		float Distance = FVector::Dist(Character->GetActorLocation(), Location);
		if (ClosestCharacter == nullptr || Distance < ClosestDistance)
		{
			ClosestCharacter = Character;
			ClosestDistance = Distance;
		}
	}
	return ClosestCharacter;
}
