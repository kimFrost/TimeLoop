// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TimeActor.h"
#include "TimeField.generated.h"


USTRUCT(BlueprintType)
struct FST_TimeEntry
{
	GENERATED_USTRUCT_BODY()
public:
	FST_TimeEntry(float Time = 0.f, TArray<FVector> Transforms = TArray<FVector>())
		: Time(Time)
		, Transforms(Transforms)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	TArray<FVector> Transforms;
};



UCLASS()
class TIMELOOP_API ATimeField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeField(const FObjectInitializer &ObjectInitializer);


	// Actors in field
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	TArray<ATimeActor*>	ActorsInField;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	bool bIsPlaying;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	bool bIsRecording;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	int PlayDirection;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float PlayRate;

	//!! Time entry instead of vector !!//
	TMap<AActor*, TArray<FST_TimeEntry>> Timeline;


	UFUNCTION(BlueprintCallable, Category = "Time")
	void SetTimeRate(float Rate);

	UFUNCTION(BlueprintCallable, Category = "Time")
	void StartRecording();

	UFUNCTION(BlueprintCallable, Category = "Time")
	void StartPlaying(bool EnableCollision = false);

	UFUNCTION(BlueprintCallable, Category = "Time")
	void Update();

	UFUNCTION(BlueprintCallable, Category = "Time")
	void Record();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	// update ActorsInField every second ??
	
};