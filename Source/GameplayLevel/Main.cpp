#include "Main.h"
#include "GameFramework/PlayerController.h"
#include "HealthScoreWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AMain::AMain()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMain::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();
	
		MainMenu = CreateWidget<UStartCallingWidget>(Controller, MainMenuClass);

		MainMenu->OnPressStart.BindUObject(this, &AMain::StartGame);
		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MainMenu)
		{
			//let add it to the view port
			MainMenu->AddToViewport();
		}

	
		// Create the widget and store it.
		HealthScoreUI = CreateWidget<UHealthScoreWidget>(Controller, HealthScoreWidgetClass);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (HealthScoreUI)
		{
			//let add it to the view port
			HealthScoreUI->AddToViewport();
		}

	SpawnerBalls = new BallSpawner(Bat);
	BonusesFactory = new BonusFactory(SpawnerBalls,Bat,BonusesConfig,GetWorld());

	CallMenu();
}

void AMain::Destroyed()
{
	delete BonusesFactory;
	delete SpawnerBalls;
}

void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMain::StartGame()
{
	HideMenu();
	BlockSpawner->DestroyAllBlocks();
	BlockSpawner->OnAllBlocksDestroyed.BindUObject(this, &AMain::EndGame);
	SpawnerBalls->OnAllBallDestroyed.BindUObject(this, &AMain::Lose);
	BlockSpawner->OnDestroyBlock.BindUObject(this, &AMain::OnBlockDestroy);
	BlockSpawner->SpawnBlocks();
	SpawnerBalls->SpawnBall();
	CurrentScore=0;
	HealthScoreUI->SetScore(0);
	CurrentHealth=MaxHealth;
	HealthScoreUI->SetHealth(CurrentHealth);
	BonusesFactory->RevertBonuses();
}

void AMain::EndGame()
{
	BlockSpawner->OnAllBlocksDestroyed.Unbind();
	SpawnerBalls->OnAllBallDestroyed.Unbind();
	BlockSpawner->OnDestroyBlock.Unbind();
	SpawnerBalls->DestroyAllBall();
	CallMenu();
}

void AMain::CallMenu()
{
	MainMenu->SetVisibility(ESlateVisibility::Visible);
	Controller->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_UIOnly(Controller);
}

void AMain::HideMenu()
{
	MainMenu->SetVisibility(ESlateVisibility::Hidden);
	Controller->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(Controller);
}

void AMain::OnBlockDestroy(ABlockBase* Block)
{
	CurrentScore++;
	HealthScoreUI->SetScore(CurrentScore);

	BonusesFactory->SpawnBonusWithProbability((Block->GetTransform().GetLocation()),BonusProbability);
}

void AMain::Lose()
{
	CurrentHealth--;
	HealthScoreUI->SetHealth(CurrentHealth);
	if(CurrentHealth<=0)
	{
		EndGame();
	}
	else
	{
		SpawnerBalls->SpawnBall();
	}
}

