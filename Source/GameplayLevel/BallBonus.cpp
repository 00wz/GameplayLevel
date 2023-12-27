// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBonus.h"

void ABallBonus::EnableBonus()
{
	BallSpawner->SpawnBall();
}

void ABallBonus::DisableBonus()
{
}
