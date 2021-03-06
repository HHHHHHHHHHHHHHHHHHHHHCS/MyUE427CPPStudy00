// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"

#include "Components/StaticMeshComponent.h"


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

	InitForce = FVector(0.0f);
	InitTorque = FVector(0.0f);
	bAccelChange = false;
}


// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	PlacedLocation = GetActorLocation();
	if (bGotoInitLocation)
	{
		SetActorLocation(InitLocation);
	}

	//StaticMesh->AddForce(InitForce, "NAME_None", bAccelChange);
	//StaticMesh->AddTorque(InitTorque);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldMove)
	{
		FHitResult hitResult;
		AddActorLocalOffset(TickLocationOffset * DeltaTime, true, &hitResult);
		// UE_LOG(LogTemp, Warning, TEXT("X: %F, Y:%F, Z: %F")
		// , hitResult.Location.X, hitResult.Location.Y, hitResult.Location.Z);
	}
}
