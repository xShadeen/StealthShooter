// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StealthShooter_cppGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHSHOOTER_CPP_API AStealthShooter_cppGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PawnKilled(APawn* PawnKilled);
	
};
