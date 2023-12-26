#pragma once

#include "..\..\Source\GameplayLevel\BatBase.h"
#include "..\..\Source\GameplayLevel\BallBase.h"
#include "..\..\Intermediate\ProjectFiles\Delegates.h"

class BallSpawner
{
public:
	BallSpawner(ABatBase* Bat);

	~BallSpawner();

	void SpawnBall();

	void DestroyAllBall();

	NoParamDelegate OnAllBallDestroyed;

	TArray<ABallBase*>* GetBallsList();

private:
	TArray<ABallBase*> Balls;

	ABatBase* Bat;

	void RemoveBall(ABallBase* Ball);
};

