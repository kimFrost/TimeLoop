// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "TimeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TIMELOOP_API ATimeGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	// Sets default values for this's properties
	ATimeGameMode(const FObjectInitializer &ObjectInitializer);

	//~~ TIME ~~//

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float CurrentTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float DayLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	bool TimeTicking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float TimeSpeed;

	
	UFUNCTION(BlueprintCallable, Category = "Time")
	void SetTimeRate(float Rate);
	
	//~~ Overrides ~~//

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	
};
