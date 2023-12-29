// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MainCharacter.h"

void AAI_Controller::BeginPlay()
{
    Super::BeginPlay();

}

void AAI_Controller::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

bool AAI_Controller::IsDead() const
{
    AMainCharacter* ControlledCharacter = Cast<AMainCharacter>(GetPawn());
    if(ControlledCharacter)
    {
        return ControlledCharacter->IsDead();
    }
    return true;
}
