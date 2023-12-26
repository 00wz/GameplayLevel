// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallSpawner.h"
#include "BonusesConfig.h"

/**
 * 
 */
class GAMEPLAYLEVEL_API BonusFactory
{
public:
	BonusFactory(BallSpawner* BallSpawner,ABatBase* BatBase,
		UBonusesConfig* BonusesConfig,UWorld* World);
	
	void SpawnBonus(FVector Position);
	
	void SpawnBonusWithProbability(FVector Position, float Probability);

	void RevertBonuses();
	
private:
	BallSpawner* BallSpawner;
	
	ABatBase* BatBase;

	float BonusFallSpeed;

	UBonusesConfig* BonusesConfig;
	
	UWorld* World;

	TArray<ABonusBase*> Bonuses;
};
