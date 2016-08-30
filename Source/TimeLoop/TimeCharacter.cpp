// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeLoop.h"
#include "TimeCharacter.h"


// Sets default values
ATimeCharacter::ATimeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATimeCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

