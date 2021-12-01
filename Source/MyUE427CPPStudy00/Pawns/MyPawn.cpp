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

	// RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	// MyStaticMesh->SetupAttachment(GetRootComponent());
	RootComponent = MyStaticMesh;

	MyStaticMesh->SetCollisionProfileName(TEXT("Pawn"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		StaticMaterialAsset(
			TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));

	if (StaticMeshAsset.Succeeded() && StaticMeshAsset.Succeeded())
	{
		MyStaticMesh->SetStaticMesh(StaticMeshAsset.Object);
		MyStaticMesh->SetMaterial(0, StaticMaterialAsset.Object);
	}

	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	MySpringArm->SetupAttachment(GetMyStaticMesh());
	MySpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	MySpringArm->TargetArmLength = 400.0f;
	MySpringArm->bEnableCameraLag = true;
	MySpringArm->CameraLagSpeed = 3.0f;

	MyCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MyCameraComponent->SetupAttachment(GetMySpringArm()); //GetRootComponent());
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

	//X, Y, Z
	//Row, Pitch, Yaw
	FRotator NewSpringArmRotation = MySpringArm->GetComponentRotation();
	NewSpringArmRotation.Pitch += MouseInput.Y;
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch, -80.0f, 40.0f);

	MySpringArm->SetWorldRotation(NewSpringArmRotation);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyPawn::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMyPawn::LookRight);
}

FORCEINLINE UStaticMeshComponent* AMyPawn::GetMyStaticMesh() const
{
	return MyStaticMesh;
}

USpringArmComponent* AMyPawn::GetMySpringArm() const
{
	return MySpringArm;
}


void AMyPawn::MoveForward(float value)
{
	Velocity.X = FMath::Clamp(value, -1.f, 1.f) * MaxSpeed;
}

void AMyPawn::MoveRight(float value)
{
	Velocity.Y = FMath::Clamp(value, -1.f, 1.f) * MaxSpeed;
}

void AMyPawn::LookUp(float value)
{
	MouseInput.Y = FMath::Clamp(value, -1.f, 1.f);
}

void AMyPawn::LookRight(float value)
{
	MouseInput.X = FMath::Clamp(value, -1.f, 1.f);
}
