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
	
	CurrentRotation = GetOwner()->GetActorRotation();
	TargetYaw += CurrentRotation.Yaw;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Debugging Logs
	UE_LOG(LogTemp, Warning, TEXT("Actor Name ---> %s"), *GetOwner()->GetName());
	UE_LOG(LogTemp, Warning, TEXT("%s's Rotation ---> %s"), *GetOwner()->GetName(), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("%s's Current Yaw Value ---> %f."),  *GetOwner()->GetName(), GetOwner()->GetActorRotation().Yaw);
	
	CurrentRotation = GetOwner()->GetActorRotation();
	CurrentYaw = CurrentRotation.Yaw;
	NewRotation.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 1.f);
	GetOwner()->SetActorRotation(NewRotation);
}
