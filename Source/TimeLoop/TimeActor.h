// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TimeActor.generated.h"

UCLASS()
class TIMELOOP_API ATimeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeActor();

	float FindMe;

	// Static Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeActor")
	UStaticMeshComponent* BaseMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
