// Copyright Adam Joyce 2017.

#pragma once

#include "GameFramework/Actor.h"
#include "LockedDoor.generated.h"

UCLASS()
class SLEUTH_API ALockedDoor : public AActor
{
    GENERATED_BODY()

    /* Visible mesh component for the door. */
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* DoorMesh;

    /* The activation zone to open the door. */
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerZone;

    /* Called when the game starts or when spawned. */
    virtual void BeginPlay() override;
	
public:	
	// Sets default values for this actor's properties
	ALockedDoor();

    /* Called when the player overlaps the trigger zone. */
    UFUNCTION(BlueprintCallable, Category = "OnOverlap")
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
