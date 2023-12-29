// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterController.h"
#include "Blueprint/UserWidget.h"



// void AMainCharacterController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
// {
//     Super::GameHasEnded(EndGameFocus, bIsWinner);

//     FString CurrentLevelName = *GetWorld()->GetMapName();

//     if(bIsWinner)
//     {
//         UUserWidget *WinScreen = CreateWidget(this, WinScreenClass);
//         UUserWidget *GameEndedScreen = CreateWidget(this, GameEndedClass);
//         if(WinScreen && CurrentLevelName=="UEDPIE_0_Urban_Map")
//         {
//             WinScreen->AddToViewport();
            
//         }        
        
//         if(GameEndedScreen && CurrentLevelName!="UEDPIE_0_Urban_Map")
//         {
//             GameEndedScreen->AddToViewport();
//         }
//     }
//     else
//     {
//         UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);
//         if(LoseScreen)
//         {
//             LoseScreen->AddToViewport();
//         }  
//     }
// }
