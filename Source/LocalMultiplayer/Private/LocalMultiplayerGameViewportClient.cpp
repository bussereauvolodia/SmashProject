// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerGameViewportClient.h"

#include "LocalMultiplayerSettings.h"
#include "LocalMultiplayerSubsystem.h"
#include "Kismet/GameplayStatics.h"

class ULocalMultiplayerSettings;

void ULocalMultiplayerGameViewportClient::PostInitProperties()
{
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();

	MaxSplitscreenPlayers = LocalMultiplayerSettings->GetNbKeyboardProfiles() + LocalMultiplayerSettings->nbMaxGamepads;
	Super::PostInitProperties();
}

bool ULocalMultiplayerGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	ULocalMultiplayerSubsystem* LocalMultiplayerSubsystem = GetGameInstance()->GetSubsystem<ULocalMultiplayerSubsystem>();
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();

	int PlayerIndex = -1;
	if (EventArgs.IsGamepad())
	{
		int GamepadID = EventArgs.ControllerId;

		PlayerIndex = LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromGamepadDeviceID(GamepadID);
		if (PlayerIndex != -1) LocalMultiplayerSubsystem->AssignGamepadInputMapping(PlayerIndex, ELocalMultiplayerInputMappingType::InGame);
		else
		{
			PlayerIndex = LocalMultiplayerSubsystem->AssignNewPlayerToGamepadDeviceID(GamepadID);
			LocalMultiplayerSubsystem->AssignGamepadInputMapping(PlayerIndex, ELocalMultiplayerInputMappingType::InGame);
			UGameplayStatics::GetPlayerController(GetGameInstance()->GetWorld(), PlayerIndex)->InputKey(EventArgs.Key,
					EventArgs.Event, EventArgs.AmountDepressed, EventArgs.IsGamepad());

		}
		
		return Super::InputKey(EventArgs);
	}

	
	int KeyboardProfileIndex = LocalMultiplayerSettings->FindKeyboardProfilesIndexFromKey(EventArgs.Key, ELocalMultiplayerInputMappingType::InGame);
	if (KeyboardProfileIndex != -1)
	{
		PlayerIndex = LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromKeyboardProfileIndex(KeyboardProfileIndex);
		if (PlayerIndex != -1) LocalMultiplayerSubsystem->AssignKeyboardMapping(PlayerIndex, KeyboardProfileIndex, ELocalMultiplayerInputMappingType::InGame);
		else
		{
			PlayerIndex = LocalMultiplayerSubsystem->AssignNewPlayerToKeyboardProfile(KeyboardProfileIndex);
			LocalMultiplayerSubsystem->AssignKeyboardMapping(PlayerIndex, KeyboardProfileIndex, ELocalMultiplayerInputMappingType::InGame);
			
		}

	}

	if (PlayerIndex != -1)
	{
		UGameplayStatics::GetPlayerController(GetGameInstance()->GetWorld(), PlayerIndex)->InputKey(EventArgs.Key,
					EventArgs.Event, EventArgs.AmountDepressed, EventArgs.IsGamepad());
	}
	return Super::InputKey(EventArgs);
}

bool ULocalMultiplayerGameViewportClient::InputAxis(FViewport* InViewport, FInputDeviceId InputDevice, FKey Key,
	float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	if (bGamepad == false) return Super::InputAxis(Viewport, InputDevice, Key, Delta, DeltaTime, NumSamples, bGamepad);;

	ULocalMultiplayerSubsystem* LocalMultiplayerSubsystem = GetGameInstance()->GetSubsystem<ULocalMultiplayerSubsystem>();
	
	int GamepadID = InputDevice.GetId();

	int PlayerIndex = LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromGamepadDeviceID(GamepadID);
	if (PlayerIndex != -1) LocalMultiplayerSubsystem->AssignGamepadInputMapping(PlayerIndex, ELocalMultiplayerInputMappingType::InGame);
	else
	{
		PlayerIndex = LocalMultiplayerSubsystem->AssignNewPlayerToGamepadDeviceID(GamepadID);
		LocalMultiplayerSubsystem->AssignGamepadInputMapping(PlayerIndex, ELocalMultiplayerInputMappingType::InGame);
		UGameplayStatics::GetPlayerController(GetGameInstance()->GetWorld(), PlayerIndex)->InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
		
	}

	if (PlayerIndex != -1)
	{
		UGameplayStatics::GetPlayerController(GetGameInstance()->GetWorld(), PlayerIndex)->InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
	}
	
	return Super::InputAxis(Viewport, InputDevice, Key, Delta, DeltaTime, NumSamples, bGamepad);
}
