// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmashCharacterStateMachine.h"

#include "SmashCharacterState.h"
#include "Characters/SmashCharacter.h"

void USmashCharacterStateMachine::Init(ASmashCharacter* InCharacter)
{
	Character = InCharacter;
	CreateStates();
	InitStates();

	ChangeState(ESmashCharacterStateID::Idle);
}

void USmashCharacterStateMachine::Tick(float DeltaTime)
{
	if (CurrentState == nullptr) return;
	CurrentState->StateTick(DeltaTime);
}

ASmashCharacter* USmashCharacterStateMachine::GetCharacter() const
{
	return Character;
}

void USmashCharacterStateMachine::ChangeState(ESmashCharacterStateID NextStateID)
{
	USmashCharacterState* NextState = GetState(NextStateID);
	//Do nothing if NextState not found
	if (NextState == nullptr) return;

	if (CurrentState != nullptr)
	{
		CurrentState->StateExit(NextStateID);
	}

	ESmashCharacterStateID PreviousStateID = CurrentStateID;
	CurrentStateID = NextStateID;
	CurrentState = NextState;

	if (CurrentState != nullptr)
	{
		CurrentState->StateEnter(PreviousStateID);
	}
}

USmashCharacterState* USmashCharacterStateMachine::GetState(ESmashCharacterStateID StateID)
{
	for (USmashCharacterState* State : AllStates)
	{
		if (StateID == State->GetStateID())
		{
			return State;
		}
	}

	return nullptr;
}

void USmashCharacterStateMachine::CreateStates()
{
	const USmashCharacterSettings* SmashCharacterSettings = GetDefault<USmashCharacterSettings>();
	TMap<ESmashCharacterStateID, TSubclassOf<USmashCharacterState>> StatesFromSettings = SmashCharacterSettings->SmashCharacterStates;
	TMap<ESmashCharacterStateID, TSubclassOf<USmashCharacterState>> StatesOverrides = Character->SmashCharacterStatesOverride;
	
	for (TTuple<ESmashCharacterStateID, TSubclassOf<USmashCharacterState>> StateFromSetting : StatesFromSettings)
	{
		if (StateFromSetting.Key == ESmashCharacterStateID::None) continue;
		
		TSubclassOf<USmashCharacterState>* State;
		
		if (StatesOverrides.Contains(StateFromSetting.Key)) State = &StatesOverrides[StateFromSetting.Key];
		else State = &StateFromSetting.Value;
		
		if (State == nullptr) continue;

		USmashCharacterState* StateObject = NewObject<USmashCharacterState>(this, *State);
		AllStates.Add(StateObject);
	}
}

void USmashCharacterStateMachine::InitStates()
{
	for (USmashCharacterState* State : AllStates)
	{
		State->StateInit(this);
	}
}
