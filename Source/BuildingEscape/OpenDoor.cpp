// Copyright Garret Browning 2021

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	CurrentRotation = GetOwner()->GetActorRotation();
	InitialYaw = CurrentRotation.Yaw;
	OpenAngle += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but no PressurePlate is set (currently set to none.)"), *GetOwner()->GetName());
	}
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		// Door Timer
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() >= DoorLastOpened + DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
		
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// Debugging Logs:
	// UE_LOG(LogTemp, Warning, TEXT("Actor Name ---> %s"), *GetOwner()->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("%s's Rotation ---> %s"), *GetOwner()->GetName(), *GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("%s's Current Yaw Value ---> %f."),  *GetOwner()->GetName(), GetOwner()->GetActorRotation().Yaw);
	
	CurrentRotation = GetOwner()->GetActorRotation();
	CurrentYaw = CurrentRotation.Yaw;
	NewRotation.Yaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	GetOwner()->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentRotation = GetOwner()->GetActorRotation();
	CurrentYaw = CurrentRotation.Yaw;
	NewRotation.Yaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);
	GetOwner()->SetActorRotation(NewRotation);
}

/*
	Choose Magic Object to Open Door dropped inside of trigger volume.
	Create GrabObject Component which inherits OpenDoor?
		- Give any component that uses GrabObject isGrabbed component, and give Player Actor/Pawn grabbing permissions (pickup/drop 1 item at a time)
		- isGrabbed = false, and WeightValue assessed.
		- if(WeightValue >= TargetWeight){OpenDoor(DeltaTime);}
	There will be 2 different objects: 1 heavier than TargetWeight and 1 lighter.
	Objects will have lightsources to indicate importance (can use the inital lights I've already Created!)
*/