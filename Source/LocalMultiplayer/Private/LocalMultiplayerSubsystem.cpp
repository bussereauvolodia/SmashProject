// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSubsystem.h"

#include "EnhancedInputSubsystems.h"
#include "LocalMultiplayerSettings.h"
#include "Kismet/GameplayStatics.h"

void ULocalMultiplayerSubsystem::CreateAndInitPlayers(ELocalMultiplayerInputMappingType MappingType)
{
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();


	for (int i = 0; i < LocalMultiplayerSettings->GetNbKeyboardProfiles() + LocalMultiplayerSettings->nbMaxGamepads; ++i)
	{
		APlayerController* PlayerController = UGameplayStatics::CreatePlayer(GetWorld(), i);	
	}
	
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromKeyboardProfileIndex(int KeyboardProfileIndex)
{
	int* PlayerIndex = PlayerIndexFromKeyboardProfileIndex.Find(KeyboardProfileIndex);
	return PlayerIndex==nullptr?-1:*PlayerIndex;
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToKeyboardProfile(int KeyboardProfileIndex)
{
	int temp = LastAssignedPlayerIndex;
	PlayerIndexFromKeyboardProfileIndex.Add(KeyboardProfileIndex, LastAssignedPlayerIndex);
	LastAssignedPlayerIndex++;
	return temp;
}

void ULocalMultiplayerSubsystem::AssignKeyboardMapping(int PlayerIndex, int KeyboardProfileIndex,ELocalMultiplayerInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	ULocalPlayer* LocalPlayer = GetGameInstance()->GetLocalPlayerByIndex(PlayerIndex);
	
	UInputMappingContext* InputMappingContext = LocalMultiplayerSettings->KeyboardProfilesData[KeyboardProfileIndex].GetIMCFromType(MappingType);
	
	FModifyContextOptions ModifyContextOptions;
	ModifyContextOptions.bForceImmediately = true;
	LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(InputMappingContext, 0, ModifyContextOptions);
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromGamepadDeviceID(int DeviceID)
{
	int* PlayerIndex = PlayerIndexFromGamepadDeviceID.Find(DeviceID);
	return PlayerIndex==nullptr?-1:*PlayerIndex;
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToGamepadDeviceID(int DeviceID)
{
	int temp = LastAssignedPlayerIndex;
	PlayerIndexFromGamepadDeviceID.Add(DeviceID, LastAssignedPlayerIndex);
	LastAssignedPlayerIndex++;
	return temp;
}

void ULocalMultiplayerSubsystem::AssignGamepadInputMapping(int PlayerIndex, ELocalMultiplayerInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	ULocalPlayer* LocalPlayer = GetGameInstance()->GetLocalPlayerByIndex(PlayerIndex);
	if (LocalPlayer == nullptr) return;

	FModifyContextOptions ModifyContextOptions;
	ModifyContextOptions.bForceImmediately = true;
	LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(LocalMultiplayerSettings->GamepadProfileData.GetIMCFromType(MappingType), 0, ModifyContextOptions);
}
