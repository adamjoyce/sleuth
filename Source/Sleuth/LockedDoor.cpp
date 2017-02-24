// Copyright Adam Joyce 2017.

#include "Sleuth.h"
#include "LockedDoor.h"
#include "EnemyCharacter.h"
#include "BaseCharacter.h"


ALockedDoor::ALockedDoor() : IsLocked(true),
                             IsPlayerOverlapping(false),
                             TriggeringCharacter(nullptr)
{
 	/// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    /// Create the visible door mesh.
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;

    /// Create the trigger zone for the door.
    TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
    TriggerZone->SetupAttachment(RootComponent);

    Materials.Init(nullptr, 2);
}

//void ALockedDoor::BeginPlay()
//{
//    /*if (TriggerZone)
//    {
//        TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ALockedDoor::OnOverlapBegin);
//    }*/
//}

bool ALockedDoor::IsTriggeringCharacterValid(ABaseCharacter* TriggeringActor)
{
    /// The door is unlocked and the actor is the player.
    if (TriggeringActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        /// This is called bot on entering and leaving the trigger zone.
        SetIsPlayerOverlapping(!GetIsPlayerOverlapping());
        SetTriggeringCharacter(TriggeringActor);

        if (!IsLocked)
        {
            return true;
        }
    }

    /// The actor is an enemy character.
    if (TriggeringActor->IsA(AEnemyCharacter::StaticClass()))
    {
        return true;
    }

    return false;
}

bool ALockedDoor::GetIsLocked()
{
    return IsLocked;
}

void ALockedDoor::SetIsLocked(bool Locked)
{
    IsLocked = Locked;

    /// Change the door material depending on if it is locked.
    if (IsLocked)
        DoorMesh->SetMaterial(0, Materials[1]);
    else
        DoorMesh->SetMaterial(0, Materials[0]);
}

bool ALockedDoor::GetIsPlayerOverlapping()
{
    return IsPlayerOverlapping;
}

void ALockedDoor::SetIsPlayerOverlapping(bool PlayerOvelapping)
{
    IsPlayerOverlapping = PlayerOvelapping;
}

ABaseCharacter* ALockedDoor::GetTriggeringCharacter()
{
    return TriggeringCharacter;
}

void ALockedDoor::SetTriggeringCharacter(ABaseCharacter* Character)
{
    TriggeringCharacter = Character;
}

//void ALockedDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//    /// Check the overlapping actor is the player.
//    if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
//    {
//        UE_LOG(LogTemp, Warning, TEXT("OPENDOOR"));
//    }
//}

