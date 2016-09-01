// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeLoop.h"
#include "TimeActor.h"


// Sets default values
ATimeActor::ATimeActor()
{


	USceneComponent* const TranslationComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	TranslationComp->Mobility = EComponentMobility::Static;
	RootComponent = TranslationComp;

	//~~ BaseMesh ~~//
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BaseMeshObj(TEXT("StaticMesh'/Game/Island/Meshes/Tile/tile.tile'"));
	if (BaseMeshObj.Succeeded())
	{
		BaseMesh->SetStaticMesh(BaseMeshObj.Object);
	}
	BaseMesh->AttachParent = RootComponent;



 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
