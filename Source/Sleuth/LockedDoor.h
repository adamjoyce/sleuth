// Copyright Adam Joyce 2017.

#pragma once

#include "GameFramework/Actor.h"
#include "LockedDoor.generated.h"

UCLASS()
class SLEUTH_API ALockedDoor : public AActor
{
    GENERATED_BODY()

    /* Is the door locked? */
    bool IsLocked;

    /* If the player is currently overlapping the door. */
    bool IsPlayerOverlapping;

    /* Triggering player character. */
    ABaseCharacter* TriggeringCharacter;

    /* Visible mesh component for the door. */
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* DoorMesh;

    /* The activation zone to open the door. */
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerZone;

    /* Materials for the sight cone. */
    UPROPERTY(EditDefaultsOnly, Category = "Materials")
    TArray<UMaterial*> Materials;

    ///* Called when the game starts or when spawned. */
    //virtual void BeginPlay() override;
	
public:	
	// Sets default values for this actor's properties
	ALockedDoor();

    /* Checks if the triggering actor is the player or an enemy. */
    UFUNCTION(BlueprintCallable, Category = "Door Functions")
    bool IsTriggeringCharacterValid(ABaseCharacter* TriggeringActor);

    /* Returns the door's locked state. */
    UFUNCTION(BlueprintCallable, Category = "Door Functions")
    bool GetIsLocked();

    /* Sets whether the door is locked. */
    UFUNCTION(BlueprintCallable, Category = "Door Functions")
    void SetIsLocked(bool Locked);

    /* Returns if the player is within the trigger zone. */
    UFUNCTION(BlueprintCallable, Category = "Door Functions")
    bool GetIsPlayerOverlapping();

    /* Sets if the player is overlapping the door trigger zone. */
    UFUNCTION(BlueprintCallable, Category = "Door Functions")
    void SetIsPlayerOverlapping(bool PlayerOverlapping);

    /* Returns the player character triggering the door. */
    UFUNCTION(BlueprintCallable, Category = "Door Functions")
    ABaseCharacter* GetTriggeringCharacter();

    /* Sets the player character triggering the door. */
    UFUNCTION(BlueprintCallable, Category = "Door Functions")
    void SetTriggeringCharacter(ABaseCharacter* Character);

    /* Called when the player overlaps the trigger zone. */
   /* UFUNCTION(BlueprintCallable, Category = "OnOverlap")
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/
};
