﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MatchGameMode.generated.h"

class AASmashCharacter;
class AArenaPlayerStart;

/**
 * 
 */
UCLASS()
class SMASHUE_API AMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TArray<AASmashCharacter*> CharactersInsideArena;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AASmashCharacter> SmashCharacterClassP0;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AASmashCharacter> SmashCharacterClassP1;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AASmashCharacter> SmashCharacterClassP2;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AASmashCharacter> SmashCharacterClassP3;

private:
	void FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>& ResultsActors);

	void SpawnCharacters(const TArray<AArenaPlayerStart*>& SpawnPoints);

	TSubclassOf<AASmashCharacter> GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const;
};
