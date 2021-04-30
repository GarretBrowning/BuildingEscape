// Copyright Garret Browning 2021

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"


#define OUT

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

	FindAudioComponent();
	FindPressurePlate();
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentRotation = GetOwner()->GetActorRotation();
	CurrentYaw = CurrentRotation.Yaw;
	NewRotation.Yaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	GetOwner()->SetActorRotation(NewRotation);

	bCloseDoorSoundPlayed = false;
	if(!AudioComponent){return;}
	if(!bOpenDoorSoundPlayed)
	{
		AudioComponent->Play();
		bOpenDoorSoundPlayed = true;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentRotation = GetOwner()->GetActorRotation();
	CurrentYaw = CurrentRotation.Yaw;
	NewRotation.Yaw = FMath::FInterpConstantTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);
	GetOwner()->SetActorRotation(NewRotation);

	bOpenDoorSoundPlayed = false;
	if(!AudioComponent){return;}
	if(!bCloseDoorSoundPlayed)
	{
		AudioComponent->Play();
		bCloseDoorSoundPlayed = true;
	}
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s - Missing Audio Component!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindPressurePlate()
{
		if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but no PressurePlate is set (currently set to none.)"), *GetOwner()->GetName());
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	TArray<UPrimitiveComponent*> OverlappingComponents;
	PressurePlate->GetOverlappingComponents(OUT OverlappingComponents); // Find all overlapping actors.

	// Add up all overlapping component masses:
	if (PressurePlate)
	{
		for (UPrimitiveComponent* Component : OverlappingComponents)
		{
			TotalMass += Component->GetMass();
		}
	}
	
	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(TotalMassOfActors() >= MassToOpenDoors)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds(); // Door timer.
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() >= DoorLastOpened + DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}