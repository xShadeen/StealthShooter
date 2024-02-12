// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "StealthShooter_cppGameModeBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"



AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	SpringArm = FindComponentByClass<USpringArmComponent>();
	PlayerCamera = FindComponentByClass<UCameraComponent>();

	if(GunClass)
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunClass);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("gun"));
		Gun->SetOwner(this);

	}


	UUserWidget* Crosshair = CreateWidget(GetWorld(), CrosshairClass);
	if(Crosshair)
	{
		Crosshair->AddToViewport();
	}

}

bool AMainCharacter::IsDead() const
{
	return Health <= 0;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UE_LOG(LogTemp, Display, TEXT("Your message %s"), *GetWorld()->GetMapName());

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMainCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AMainCharacter::StopJump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &AMainCharacter::StartCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &AMainCharacter::StopCrouch);
	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Pressed, this, &AMainCharacter::StartWalk);
	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Released, this, &AMainCharacter::StopWalk);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AMainCharacter::Shoot);

}

float AMainCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float DamageToApply = FMath::Min(DamageAmount, Health);
	Health -= DamageToApply;

	AStealthShooter_cppGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AStealthShooter_cppGameModeBase>();

	if(IsDead() && GameMode)
	{
		GameMode->PawnKilled(this);

		Gun->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		Gun->SetGunPhysics(true);
		Gun->SetGunMobility(EComponentMobility::Movable);
		UPrimitiveComponent* CollisionPreset = Gun->FindComponentByClass<UPrimitiveComponent>();
		if (CollisionPreset)
		{
			CollisionPreset->SetCollisionProfileName(TEXT("PhysicsActor"));
		}
		
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    }

	return DamageToApply;
}

void AMainCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AMainCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AMainCharacter::StartJump()
{
	if(GetCharacterMovement()->IsMovingOnGround())
	{
		Jump();
		isJumping = true;
	}
}

void AMainCharacter::StopJump()
{
	StopJumping();
	isJumping = false;
}

void AMainCharacter::StartCrouch()
{
	if(GetCharacterMovement()->IsMovingOnGround())
	{
		Crouch();
		isCrouching = true;		
		if(SpringArm)
		{
			SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f), false);
		}
	}

}

void AMainCharacter::StopCrouch()
{
	UnCrouch();
	isCrouching = false;
	if(SpringArm)
	{
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f), false);
	}
}

void AMainCharacter::StartWalk()
{
	if(!isCrouching)
	{
		isWalking = true;
		GetCharacterMovement()->MaxWalkSpeed = 450.f;
	}
}

void AMainCharacter::StopWalk()
{
	isWalking = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	
}

void AMainCharacter::Shoot()
{
	Gun->PullTrigger();
}



