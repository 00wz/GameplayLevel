// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Main.h"
#include "BatBase.h"

// Sets default values
AMain::AMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();

	Controller = Controller = GetWorld()->GetFirstPlayerController();

	if (MainMenuClass) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MainMenu = CreateWidget<UStartCallingWidget>(Controller, MainMenuClass);

		MainMenu->OnPressStart.BindUObject(this, &AMain::StartGame);
		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MainMenu)
		{
			//let add it to the view port
			MainMenu->AddToViewport();
		}
	}

	SpawnerBalls = new BallSpawner(Bat);
}

void AMain::Destroyed()
{
	delete SpawnerBalls;
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMain::StartGame()
{
	HideMenu();
	BlockSpawner->DestroyAllBlocks();
	BlockSpawner->OnAllBlocksDestroyed.BindUObject(this, &AMain::EndGame);
	SpawnerBalls->OnAllBallDestroyed.BindUObject(this, &AMain::EndGame);
	BlockSpawner->SpawnBlocks();
	SpawnerBalls->SpawnBall();
}

void AMain::EndGame()
{
	BlockSpawner->OnAllBlocksDestroyed.Unbind();
	SpawnerBalls->OnAllBallDestroyed.Unbind();
	SpawnerBalls->DestroyAllBall();
	CallMenu();
}

void AMain::CallMenu()
{
	MainMenu->SetVisibility(ESlateVisibility::Visible);
	Controller->SetShowMouseCursor(true);
}

void AMain::HideMenu()
{
	MainMenu->SetVisibility(ESlateVisibility::Hidden);
	Controller->SetShowMouseCursor(false);
}

