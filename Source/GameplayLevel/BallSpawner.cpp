
#include "BallSpawner.h"

BallSpawner::BallSpawner(ABatBase* Bat)
{
	this->Bat = Bat;
}

BallSpawner::~BallSpawner()
{
	for (int i = 0;i < Balls.Num();i++) 
	{
		Balls[i]->OnDestroyBall.Unbind();
	}
}

void BallSpawner::SpawnBall()
{
	auto Ball = Bat->SpawnBall();
	Balls.Add(Ball);
	Ball->OnDestroyBall.BindRaw(this, &BallSpawner::RemoveBall);
}

void BallSpawner::RemoveBall(ABallBase* Ball)
{
	Balls.Remove(Ball);
	if (Balls.Num() <= 0)
	{
		OnAllBallDestroyed.ExecuteIfBound();
	}
}

void BallSpawner::DestroyAllBall()
{		
	for (int i = Balls.Num() - 1;i >= 0;i--)
	{
		Balls[i]->Destroy();
	}
}

TArray<ABallBase*>* BallSpawner::GetBallsList()
{
	return new TArray<ABallBase*>(Balls);
}
