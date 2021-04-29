// Copyright Garret Browning 2021

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation = GetOwner()->GetActorLocation();
	FRotator PlayerViewPointRotation = GetOwner()->GetActorRotation();

	// Get players viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	UE_LOG(LogTemp, Warning, TEXT("PlayerViewPointLocation: %s || PlayerViewPointRotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	
	// Ray-cast out to a certain distance (Reach)

	// See what you get
}

