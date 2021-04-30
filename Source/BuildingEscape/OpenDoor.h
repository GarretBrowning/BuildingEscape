// Copyright Garret Browning 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

	float TotalMassOfActors() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FRotator CurrentRotation;
	FRotator NewRotation;
	float InitialYaw;
	float CurrentYaw;
	
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f; // Initial angle set to add 90 degrees to the door's current Yaw value.

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.33f; // Default time delay that a door will close.

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.f; // Default opening speed of a door (used within an exponential interpolation).

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 270.f; // Default closing speed of a door (used within a constant linear interpolation)
	
	UPROPERTY(EditAnywhere)
	float MassToOpenDoors = 50.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
};