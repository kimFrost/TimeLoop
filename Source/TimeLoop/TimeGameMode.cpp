// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeLoop.h"
#include "TimePlayerControllerBase.h"
#include "TimeGameMode.h"



// Sets default values
ATimeGameMode::ATimeGameMode(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentTime = 0.f;
	DayLength = 300.f;
	TimeTicking = false;
	TimeSpeed = 1.f;

	//~~ Set the default PlayerController ~~ //
	PlayerControllerClass = ATimePlayerControllerBase::StaticClass();
}


void ATimeGameMode::SetTimeRate(float Rate)
{
	TimeSpeed = Rate;
}


void ATimeGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATimeGameMode::BeginPlay()
{
	Super::BeginPlay();

}