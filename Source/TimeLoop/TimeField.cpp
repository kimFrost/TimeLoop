// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeLoop.h"
#include "TimeActor.h"
#include "TimeField.h"


// Sets default values
ATimeField::ATimeField(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	bIsPlaying = false;
	bIsRecording = false;
	PlayDirection = -1;
	PlayRate = 1.f;


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATimeField::SetTimeRate(float Rate)
{
	PlayRate = Rate;
}


void ATimeField::StartPlaying(bool EnableCollision)
{
	for (auto& Actor : ActorsInField)
	{
		if (!EnableCollision)
		{
			//Disable physics and put to sleep.

		}
		else
		{
			// Disable physics and collision + put to sleep. Performance boost!
		}
	}
}


void ATimeField::StartRecording()
{
	for (auto& Actor : ActorsInField)
	{
		// Enable physic and collision + wake
		//Actor->FindMe;
	}
}


void ATimeField::Update()
{
	if (bIsRecording)
	{
		Record();
	}
	else if (bIsPlaying)
	{
		for (auto& Actor : ActorsInField)
		{
			//Actor->GetPhysi
		}
	}
}


void ATimeField::Record()
{
	for (auto& Actor : ActorsInField)
	{

	}
}

// Called when the game starts or when spawned
void ATimeField::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeField::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	Update(); //!! Call on timer instead of tick 1000 / 60 or 30. 30 is less precise!
}

