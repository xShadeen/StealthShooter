// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "MainCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Supprocessor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Supprocessor"));
	Supprocessor->SetupAttachment(Mesh);


}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlash"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(!OwnerPawn) return;
	AController* OwnerController = OwnerPawn->GetController();
	if(!OwnerController) return;

	FVector Location;
	FRotator Rotation;

	if(!Mesh) return;

	FVector MuzzleFlashLocation = Mesh->GetSocketLocation(TEXT("MuzzleFlash"));

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	

	FHitResult Hit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);

	if(bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector();
		
		if (Hit.ImpactPoint == FVector::ZeroVector)
		{
			FHitResult SecondaryHit;
			
			bool bSecondarySuccess = GetWorld()->LineTraceSingleByChannel(SecondaryHit, MuzzleFlashLocation, Hit.TraceEnd, ECollisionChannel::ECC_GameTraceChannel1);

			if (bSecondarySuccess)
			{
				Hit = SecondaryHit;
			}
		}
		else
		{
			FHitResult SecondaryHit;
			bool bSecondarySuccess = GetWorld()->LineTraceSingleByChannel(SecondaryHit, MuzzleFlashLocation, Hit.ImpactPoint, ECollisionChannel::ECC_GameTraceChannel1);

			if (bSecondarySuccess)
			{
				Hit = SecondaryHit;
			}
		}
		
		if(Hit.GetActor()->IsA<AMainCharacter>())
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			Hit.GetActor()->TakeDamage(Damage, DamageEvent, OwnerController, this);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffectActorHitted, Hit.Location, ShotDirection.Rotation());
		}
		else
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		}
	}

	if (ShotSound)
	{
		UGameplayStatics::SpawnSoundAttached(ShotSound, Mesh, TEXT("MuzzleFlash"));
	}
}

void AGun::SetGunPhysics(bool bSimulatePhysics)
{
    if (Mesh)
    {
        Mesh->SetSimulatePhysics(bSimulatePhysics);
    }

}

void AGun::SetGunMobility(EComponentMobility::Type Mobility)
{
    if (Mesh)
    {
        Mesh->SetMobility(Mobility);
    }

}


