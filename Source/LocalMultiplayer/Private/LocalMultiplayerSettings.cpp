// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSettings.h"

#include "InputMappingContext.h"


int ULocalMultiplayerSettings::GetNbKeyboardProfiles() const
{
	return KeyboardProfilesData.Num();
}

int ULocalMultiplayerSettings::FindKeyboardProfilesIndexFromKey(const FKey Key, ELocalMultiplayerInputMappingType MappingType) const
{
	for (int i = 0; i < KeyboardProfilesData.Num(); i++)
	{
		if (KeyboardProfilesData[i].ContainsKey(Key, MappingType))
		{
			return i;
		}
	}
	
	return -1;
}

bool FLocalMultiplayerProfileData::ContainsKey(const FKey& Key, ELocalMultiplayerInputMappingType MappingType) const
{
	for (FEnhancedActionKeyMapping MappingKey : GetIMCFromType(MappingType)->GetMappings())
	{
		if (MappingKey.Key == Key){
			return true;
		}
	}
	return false;
}

UInputMappingContext* FLocalMultiplayerProfileData::GetIMCFromType(ELocalMultiplayerInputMappingType MappingType) const
{
	if (MappingType == ELocalMultiplayerInputMappingType::Menu)
	{
		return IMCMenu;
	}
	if (MappingType == ELocalMultiplayerInputMappingType::InGame)
	{
		return IMCInGame;
	}

	return nullptr;
}
