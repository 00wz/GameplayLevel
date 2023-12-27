#pragma once

#include "BallSpawner.h"
#include "SpawnerBricks.h"
#include "StartCallingWidget.h"
#include "BatBase.h"
#include "CoreMinimal.h"
#include "BonusesConfig.h"
#include "BonusFactory.h"
#include "HealthScoreWidget.h"
#include "GameFramework/Actor.h"
#include "Main.generated.h"

UCLASS()
class GAMEPLAYLEVEL_API AMain : public AActor
{
	GENERATED_BODY()
	
public:	
	AMain();

	UPROPERTY(EditAnyWhere, BlueprintReadonly)
		ABatBase* Bat;

	UPROPERTY(EditAnyWhere)
		ASpawnerBricks* BlockSpawner;

	UPROPERTY(EditAnyWhere)
		int MaxHealth;

	UPROPERTY(EditAnywhere);
		TSubclassOf<UStartCallingWidget> MainMenuClass;

	UPROPERTY(EditAnywhere);
		TSubclassOf<UHealthScoreWidget> HealthScoreWidgetClass;

	UPROPERTY(EditAnywhere)
		UBonusesConfig* BonusesConfig;

	UPROPERTY(EditAnywhere)
		float BonusProbability;

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UStartCallingWidget* MainMenu;

	UHealthScoreWidget* HealthScoreUI;
	
	void StartGame();

	void EndGame();

	void CallMenu();

	void HideMenu();

	void OnBlockDestroy(ABlockBase*);

	BallSpawner* SpawnerBalls;

	APlayerController* Controller;

	int CurrentHealth;

	int CurrentScore;

	void Lose();

	BonusFactory* BonusesFactory;
};
