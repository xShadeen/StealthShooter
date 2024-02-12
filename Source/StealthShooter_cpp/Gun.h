// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class STEALTHSHOOTER_CPP_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	UFUNCTION(BlueprintCallable, Category = "Gun")
    void SetGunPhysics(bool bSimulatePhysics);

    UFUNCTION(BlueprintCallable, Category = "Gun")
    void SetGunMobility(EComponentMobility::Type Mobility);


private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun")
	UStaticMeshComponent* Supprocessor;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffectActorHitted;

    UPROPERTY(EditAnywhere)
    class USoundBase* ShotSound;
	

	UPROPERTY(EditAnywhere)
	float MaxRange = 2000;

	UPROPERTY(EditAnywhere)
	float Damage = 100;




};
