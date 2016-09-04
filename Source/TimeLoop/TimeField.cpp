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
	CurrentTime = 0.f;


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

int ATimeField::GetTestValue()
{
	return Timeline.Num();
}


void ATimeField::SetPlayRate(float Rate)
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
			if (EnableCollision)
			{
				// Enable collision. A lot slower
				TimeActor->BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			}
			else
			{
				// Disable collision + put to sleep. Performance boost!
				TimeActor->BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				TimeActor->BaseMesh->PutRigidBodyToSleep();
			}
			// When to remove and despawn actors?? On TimeLoop exit??
		}
	}
	bIsPlaying = true;
	bIsRecording = false;
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
	bIsPlaying = false;
	bIsRecording = true;
}


void ATimeField::Update()
{
	if (bIsRecording)
	{
		RecordFrame(CurrentTime);
	}
	else if (bIsPlaying)
	{
		PlayFrame(CurrentTime);
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
		//NewEntry.Transform = TimeActor->GetActorTransform();
		NewEntry.Transform = TimeActor->BaseMesh->GetComponentTransform();
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

	StartRecording();

	//GetWorld()->GetTimerManager().SetTimer(TimeUpdateHandle, this, &ATimeField::Update, 1.f);
	//GetWorld()->GetTimerManager().SetTimer(TimeUpdateHandle, 1.f, true);

	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(TimeUpdateHandle, this, &ATimeField::Update, (1.f / 60), true, 0.f);
		//World->GetTimerManager().ClearTimer(TimeUpdateHandle);
		//World->GetTimerManager().ClearAllTimersForObject(this);
	}
}

// Called every frame
void ATimeField::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	/*
	ATimeGameMode* GameMode = (ATimeGameMode*)GetWorld()->GetAuthGameMode();
	if (GameMode)
	{
		Update(GameMode->CurrentTime); //!! Call on timer instead of tick 1000 / 60 or 30. 30 is less precise!
	}
	*/

	CurrentTime += (DeltaTime * PlayRate);

	//Update(CurrentTime);

}

