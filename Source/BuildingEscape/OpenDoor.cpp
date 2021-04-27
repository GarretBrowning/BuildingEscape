// Copyright Garret Browning 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

//WE NEED TO FIX THIS UP BECAUSE THE DOOR ISN'T OPENING HELLOOOOOOOOOOO
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

// 	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
// 	UE_LOG(LogTemp, Warning, TEXT("%f is the Yaw."), GetOwner()->GetActorRotation().Yaw);

	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator DoorAjar(0.f, 0.f, 0.f);
	DoorAjar.Yaw = FMath::Lerp(CurrentYaw, 90.0f, 0.21f);
	GetOwner()->SetActorRotation(DoorAjar);
// 	//FMath::Lerp(/*CurrentYaw, TargetYaw, 0-1 (for percentage)*/);

// 		// FRotator CurrentRotation = GetOwner()->GetActorRotation();
// 	// CurrentRotation.Yaw = 90.f;
// 	// FRotator DoorAjar(0.f, 90.f, 0.f);

// 	GetOwner()->SetActorRotation(GetOwner()->GetActorRotation());
// 
}

