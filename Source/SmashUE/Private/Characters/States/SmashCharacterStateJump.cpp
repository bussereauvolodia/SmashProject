// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/SmashCharacterStateJump.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"

ESmashCharacterStateID USmashCharacterStateJump::GetStateID()
{
	return ESmashCharacterStateID::Jump;
}

void USmashCharacterStateJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->GetCharacterMovement()->AirControl = JumpAirControl;
	Character->GetCharacterMovement()->MaxWalkSpeed = JumpWalkSpeed;
	Character->GetCharacterMovement()->JumpZVelocity = (2 * JumpMaxHeight) / JumpDuration;
	Character->GetCharacterMovement()->GravityScale = (-2 * JumpMaxHeight) / (JumpDuration * JumpDuration) / -980.f;
	
	Character->Jump();

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Purple,
		TEXT("Jumpiiiing")
		);
}

void USmashCharacterStateJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	if (Character->GetVelocity().Z < 0.f)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}

	if (FMath::Abs(Character->GetInputMoveX()) > CharacterSettings->InputMoveXThreshold)
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector, Character->GetOrientX());
	}
}
