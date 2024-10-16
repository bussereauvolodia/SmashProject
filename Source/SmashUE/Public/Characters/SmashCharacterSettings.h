// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SmashCharacterInputData.h"
#include "SmashCharacterSettings.generated.h"

enum class ESmashCharacterStateID : uint8;
class USmashCharacterState;
class UInputMappingContext;
class USmashCharacterInputData;
/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName = "Smash Character Settings"))
class SMASHUE_API USmashCharacterSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="States")
	TArray<ESmashCharacterStateID> PossibleStates;
	
	UPROPERTY(Config, EditAnywhere, Category="States")
	TMap<ESmashCharacterStateID, TSubclassOf<USmashCharacterState>> SmashCharacterStates;
	
	UPROPERTY(Config, EditAnywhere, Category="Inputs")
	TSoftObjectPtr<USmashCharacterInputData> InputData;

	UPROPERTY(Config, EditAnywhere, Category="Inputs")
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(Config, EditAnywhere, Category="Inputs")
	float InputMoveXThreshold;
};
