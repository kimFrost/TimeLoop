// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TimePlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class TIMELOOP_API ATimePlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
	
	
public:
	UFUNCTION(BlueprintPure, Category = "Hud")
	float GetObjectScreenRadius(AActor* InActor);

	UFUNCTION(BlueprintPure, Category = "Hud")
	FBox2D GetObjectScreenBounds(AActor* InActor);

};
