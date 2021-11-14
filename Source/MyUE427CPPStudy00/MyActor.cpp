// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	InitLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f);
	TickLocationOffset = FVector(0.0f);
}



// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	PlacedLocation = GetActorLocation();
	if(bGotoInitLocation)
	{
		SetActorLocation(InitLocation);
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bShouldMove)
	{
		AddActorLocalOffset(TickLocationOffset);
	}
}

