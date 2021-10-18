// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObject.h"

UMyObject::UMyObject()
{
	myFloat = 0.0f;
}

void UMyObject::MyFunction()
{
	UE_LOG(LogTemp, Log, TEXT("Log Text !"));
	UE_LOG(LogTemp, Warning, TEXT("Warning Text !"));
	UE_LOG(LogTemp, Error, TEXT("Error Text !"));
}
