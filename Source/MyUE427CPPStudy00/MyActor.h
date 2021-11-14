// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class MYUE427CPPSTUDY00_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(VisibleAnywhere, Category="My Actor Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditInstanceOnly, Category="My Actor Properties | Vector")
	FVector InitLocation;

	UPROPERTY(VisibleInstanceOnly, Category="My Actor Properties | Vector")
	FVector PlacedLocation;

	UPROPERTY(EditDefaultsOnly, Category="My Actor Properties | Bool")
	bool bGotoInitLocation;

	UPROPERTY(VisibleDefaultsOnly, Category="My Actor Properties | Vector")
	FVector WorldOrigin;

	UPROPERTY(EditAnywhere, Category="My Actor Properties | Vector"
		, meta=(ClampMin = -5.0f, ClampMax = 5.0f, UIMin = -5.0f, UIMax = 5.0f))
	FVector TickLocationOffset;

	UPROPERTY(EditAnywhere, Category="My Actor Properties | Bool")
	bool bShouldMove;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
