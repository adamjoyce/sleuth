// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "LockedDoor.h"


ALockedDoor::ALockedDoor()
{
 	/// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    /// Create the visible door mesh.
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;

    /// Create the trigger zone for the door.
    TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
    TriggerZone->SetupAttachment(RootComponent);
}

//void ALockedDoor::BeginPlay()
//{
//    /*if (TriggerZone)
//    {
//        TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ALockedDoor::OnOverlapBegin);
//    }*/
//}

void ALockedDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    /// Check the overlapping actor is the player.
    /*if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        UE_LOG(LogTemp, Warning, TEXT("OPENDOOR"));
    }*/
}

