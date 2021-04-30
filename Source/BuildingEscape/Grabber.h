// Copyright Garret Browning 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float Reach = 130.0f;

	UInputComponent* GrabInputComponent = nullptr;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	void FindPhysicsHandle();
	void Grab();
	void Release();
	void SetupInputComponent();

	// Returns the LineTraceEnd (Player's Reach) for grabbing purposes:
	FVector GetPlayerReach() const;

	// Gives us the Player's ViewPoint based on their position in the world:
	FVector GetPlayerWorldPosition() const;

	// Return the first Actor in reach with PhysicsBody:
	FHitResult GetFirstPhysicsBodyInReach() const;

};
