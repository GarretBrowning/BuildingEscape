// Copyright Garret Browning 2021

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

// Checking for Physics Handle Component:
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s PhysicsHandleComponent not found!"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	// Tries to reach any actors with collision channel set to PhysicsBody. If we hit something, then we attach the physics handle:
	if(ActorHit)
	{
		if(!PhysicsHandle){return;} // Protecting ourselves incase we point to nothing.
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, GetPlayerReach());
	}
}

void UGrabber::Release()
{
	if(!PhysicsHandle){return;} // Protecting ourselves incase we point to nothing.
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::SetupInputComponent()
{
	GrabInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	
	if(GrabInputComponent)
	{
		GrabInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		GrabInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Grab InputComponent MISSING!"), *GetOwner()->GetName());
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	// Ray-cast out to a certain distance (Reach):
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetPlayerWorldPosition(), GetPlayerReach(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	return Hit;
}

FVector UGrabber::GetPlayerReach() const
{
	FVector PlayerViewPointLocation = GetOwner()->GetActorLocation();
	FRotator PlayerViewPointRotation = GetOwner()->GetActorRotation();

	// Get Player's ViewPoint:
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;  // PlayerViewPointRotation.Vector() converts to a UnitVector.
}

FVector UGrabber::GetPlayerWorldPosition() const
{
	FVector PlayerViewPointLocation = GetOwner()->GetActorLocation();
	FRotator PlayerViewPointRotation = GetOwner()->GetActorRotation();

	// Get Player's ViewPoint:
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!PhysicsHandle){return;} // Protecting ourselves incase we point to nothing.
	// If the PhysicsHandle is attached -
	if (PhysicsHandle->GrabbedComponent)
	{
		// Move the object we are holding:
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}
}