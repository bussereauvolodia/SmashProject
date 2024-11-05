// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraFollowTarget.h"
#include "Kismet/GameplayStatics.h"

void UCameraWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CameraMain = FindCameraByTag(TEXT("CameraMain"));
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CameraMain != nullptr) TickUpdateCameraPosition(DeltaTime);
}

void UCameraWorldSubsystem::AddFollowTarget(UObject* FollowTarget)
{
	if (FollowTargets.Contains(FollowTarget) || FollowTarget == nullptr) return;
	FollowTargets.Add(FollowTarget);
}

void UCameraWorldSubsystem::RemoveFollowTarget(UObject* FollowTarget)
{
	if (!FollowTargets.Contains(FollowTarget) || FollowTarget == nullptr) return;
	FollowTargets.Remove(FollowTarget);
}

void UCameraWorldSubsystem::TickUpdateCameraPosition(float DeltaTime)
{
	FVector NewLocation = CalculateAveragePositionBetweenTargets();
	NewLocation.Y = CameraMain->GetComponentLocation().Y;
	CameraMain->SetWorldLocation(NewLocation);
}

FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets()
{
	FVector SumPositions = FVector::ZeroVector;
	for (UObject* FollowTarget : FollowTargets)
	{
		TScriptInterface<ICameraFollowTarget> FollowTargetInterface = FollowTarget;
		if (FollowTargetInterface == nullptr || !FollowTargetInterface->isFollowable()) continue;
		SumPositions += FollowTargetInterface->GetFollowPosition();
	}
	if (FollowTargets.Num() <= 0) return CameraMain->GetComponentLocation();
	return SumPositions / FollowTargets.Num();
}

UCameraComponent* UCameraWorldSubsystem::FindCameraByTag(const FName& Tag) const
{
	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, FoundCameras);
	for (AActor* FoundCamera : FoundCameras)
	{
		UCameraComponent* CameraComponent = Cast<UCameraComponent>(FoundCamera->GetComponentByClass(UCameraComponent::StaticClass()));
		if (CameraComponent != nullptr) return CameraComponent;
	}
	return nullptr;
}
