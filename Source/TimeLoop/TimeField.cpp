// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeLoop.h"
#include "TimeActor.h"
#include "TimeGameMode.h"
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
	for (auto& TimeActor : ActorsInField)
	{
		if (TimeActor != nullptr)
		{
			TimeActor->BaseMesh->SetSimulatePhysics(false);
			if (!EnableCollision)
			{
				// Disable collision + put to sleep. Performance boost!
				TimeActor->BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				TimeActor->BaseMesh->PutRigidBodyToSleep();
			}
			else
			{
				// Enable collision. A lot slower
				TimeActor->BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			}
			// When to remove and despawn actors?? On TimeLoop exit??
		}
	}
}


void ATimeField::StartRecording()
{
	for (auto& TimeActor : ActorsInField)
	{
		if (TimeActor != nullptr)
		{
			// Enable physic and collision + wake
			TimeActor->BaseMesh->SetSimulatePhysics(true);
			TimeActor->BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			TimeActor->BaseMesh->WakeRigidBody();
			/*
			// Check for timeline entry
			if (!Timeline.Contains(Actor)) {
				Timeline.Add(TimeActor, TArray<FST_TimeEntry>());
			}
			*/
		}
		// When to remove and despawn actors?? On TimeLoop exit??
	}
}


void ATimeField::Update(float Time)
{
	if (bIsRecording)
	{
		RecordFrame(Time);
	}
	else if (bIsPlaying)
	{
		PlayFrame(Time);
	}
}

void ATimeField::PlayFrame(float Time)
{
	if (Timeline.Num() > 0)
	{
		float ClosestMinTime = 0.f;
		float ClosestMaxTime = 0.f;
		bool bMinFound = false;
		bool bMaxFound = false;

		/*
		Timeline.KeySort([](int32 A, int32 B) {
			return A < B; // Sort from lowest to highest
		});
		*/

		TArray<float> Times;
		Timeline.GetKeys(Times);

		if (Times.Num() > 1)
		{
			for (int i = 1; i < Times.Num(); i++)
			{
				if (Times[i] >= Time)
				{
					ClosestMinTime = Times[i - 1];
					ClosestMaxTime = Times[i];
					break;
				}
			}
		}
		else
		{
			ClosestMinTime = Times[0];
			ClosestMaxTime = Times[0];
		}

		for (auto& TimeActor : ActorsInField)
		{
			//TimeActor->BaseMesh->SetPhysicsAngularVelocity
			//TimeActor->BaseMesh->SetPhysicsLinearVelocity
		}
	}
}

void ATimeField::RecordFrame(float Time)
{
	TMap<ATimeActor*, FST_TimeEntry> Entries;

	for (auto& TimeActor : ActorsInField)
	{
		FST_TimeEntry NewEntry = FST_TimeEntry();
		NewEntry.Transform = TimeActor->GetActorTransform();
		FTransform Velocities;
		Velocities.SetLocation(TimeActor->BaseMesh->GetPhysicsLinearVelocity());
		Velocities.SetScale3D(TimeActor->BaseMesh->GetPhysicsAngularVelocity());
		NewEntry.Velocity = Velocities;
		NewEntry.Time = Time;

		Entries.Add(TimeActor, NewEntry);
	}

	Timeline.Add(Time, Entries);
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

	ATimeGameMode* GameMode = (ATimeGameMode*)GetWorld()->GetAuthGameMode();
	if (GameMode)
	{
		Update(GameMode->CurrentTime); //!! Call on timer instead of tick 1000 / 60 or 30. 30 is less precise!
	}

}

