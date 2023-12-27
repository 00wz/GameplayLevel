#include "BallAccelerationBonus.h"

void ABallAccelerationBonus::EnableBonus()
{
	auto Balls=BallSpawner->GetBallsList();
	for(int i=0;i<Balls->Num();i++)
	{
		auto Ball=(*Balls)[i];
		Ball->SetMoveSpeed(Ball->GetMoveSpeed()*SpeedRatio);
	}
	delete Balls;
}

void ABallAccelerationBonus::DisableBonus()
{
	auto inverseRatio=1/SpeedRatio;
	auto Balls=BallSpawner->GetBallsList();
	for(int i=0;i<Balls->Num();i++)
	{
		auto Ball=(*Balls)[i];
		Ball->SetMoveSpeed(Ball->GetMoveSpeed()*inverseRatio);
	}
	delete Balls;
}
