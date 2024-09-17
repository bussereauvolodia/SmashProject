// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ASmashCharacter.h"


// Sets default values
AASmashCharacter::AASmashCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AASmashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASmashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AASmashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

