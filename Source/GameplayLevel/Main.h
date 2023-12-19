// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BallSpawner.h"
#include "SpawnerBricks.h"
#include "StartCallingWidget.h"
#include "BatBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Main.generated.h"

UCLASS()
class GAMEPLAYLEVEL_API AMain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMain();

	UPROPERTY(EditAnyWhere, BlueprintReadonly)
		ABatBase* Bat;

	UPROPERTY(EditAnyWhere)
		ASpawnerBricks* BlockSpawner;

	UPROPERTY(EditAnywhere);
		TSubclassOf<UStartCallingWidget> MainMenuClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UStartCallingWidget* MainMenu;

	void StartGame();

	void EndGame();

	void CallMenu();

	void HideMenu();

	BallSpawner* SpawnerBalls;

	APlayerController* Controller;
};
