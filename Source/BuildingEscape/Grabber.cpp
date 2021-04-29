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
	// Log for if Physics is not found:
	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s PhysicsHandleComponent not found!"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	GrabInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	
	if(GrabInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Grab InputComponent found!"), *GetOwner()->GetName());
		GrabInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		GrabInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Grab InputComponent MISSING"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	///////////////////////////////////////////////////////////////////////
	// TAKE THIS SHIT OUT ASAP - JUST USING FOR USABILITY:
	FVector PlayerViewPointLocation = GetOwner()->GetActorLocation();
	FRotator PlayerViewPointRotation = GetOwner()->GetActorRotation();

	// Get Player's ViewPoint:
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	
	// Draw a line from player showing the reach:
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;  // PlayerViewPointRotation.Vector() converts to a UnitVector.
	///////////////////////////////////////////////////////////////////////

	// Logs:
	UE_LOG(LogTemp, Warning, TEXT("Grabber Press"));

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();


	// Try and rech any actors with physiucs body collision channel set.
	// If we hit something then attach the physics handle
	if(HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, LineTraceEnd);
	}
	// TODO: attach physics handle.
}

void UGrabber::Release()
{
	// Logs:
	UE_LOG(LogTemp, Warning, TEXT("Grabber Release"));

	//TODO: remove/release the physics handle.
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	///////////////////////////////////////////////////////////////////////
	// TAKE THIS SHIT OUT ASAP - JUST USING FOR USABILITY:
	FVector PlayerViewPointLocation = GetOwner()->GetActorLocation();
	FRotator PlayerViewPointRotation = GetOwner()->GetActorRotation();

	// Get Player's ViewPoint:
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	
	// Draw a line from player showing the reach:
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;  // PlayerViewPointRotation.Vector() converts to a UnitVector.
	///////////////////////////////////////////////////////////////////////




	// If the physic handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object we are holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

	// GetFirstPhysicsBodyInReach();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation = GetOwner()->GetActorLocation();
	FRotator PlayerViewPointRotation = GetOwner()->GetActorRotation();

	// Get Player's ViewPoint:
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	
	// Draw a line from player showing the reach:
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;  // PlayerViewPointRotation.Vector() converts to a UnitVector.

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	// Ray-cast out to a certain distance (Reach):
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	// Getting the Actor that the LineTrace hits:
	AActor* ActorHit = Hit.GetActor();

	// Logs:
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is hit by LineTrace!"), *ActorHit->GetName());
	}

	// Creates a debug line to show the player's viewpoint:
	// DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 165, 0), false, 0.f, 0, 5.f);

	return Hit;
}
