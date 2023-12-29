// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"



class AGun;

UCLASS()
class STEALTHSHOOTER_CPP_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isCrouching = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isWalking = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isJumping = false;


public:	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:


	class USpringArmComponent* SpringArm;
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CrosshairClass;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void StartJump();
	void StopJump();
	void StartCrouch();
	void StopCrouch();
	void StartWalk();
	void StopWalk();
	void Shoot();
};
