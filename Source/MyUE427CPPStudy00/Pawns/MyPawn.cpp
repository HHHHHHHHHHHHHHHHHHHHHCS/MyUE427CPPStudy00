// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MyStaticMesh->SetupAttachment(GetRootComponent());

	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	MySpringArm->SetupAttachment(MyStaticMesh);
	MySpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	MySpringArm->TargetArmLength = 400.0f;
	MySpringArm->bEnableCameraLag = true;
	MySpringArm->CameraLagSpeed = 3.0f;

	MyCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MyCameraComponent->SetupAttachment(MySpringArm);//GetRootComponent());
	// MyCameraComponent->SetRelativeLocation(FVector(-300.0f, 0.0f, 300.0f));
	// MyCameraComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MaxSpeed = 100.0f;
	Velocity = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(Velocity * DeltaTime, true);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
}

void AMyPawn::MoveForward(float value)
{
	Velocity.X = FMath::Clamp(value, -1.f, 1.f) * MaxSpeed;
}

void AMyPawn::MoveRight(float value)
{
	Velocity.Y = FMath::Clamp(value, -1.f, 1.f) * MaxSpeed;
}
