#include "BonusFactory.h"

#include "BonusesConfig.h"

BonusFactory::BonusFactory(::BallSpawner* BallSpawner, ABatBase* BatBase, UBonusesConfig* BonusesConfig,UWorld* World)
{
	this->BallSpawner=BallSpawner;
	this->BatBase=BatBase;
	this->BonusesConfig=BonusesConfig;
	this->BonusFallSpeed=BonusesConfig->BonusFallSpeed;
	this->World = World;
}


void BonusFactory::SpawnBonus(FVector Position)
{
	auto index=FMath::RandRange(0,BonusesConfig->BonusClasses.Num()-1);
	auto Bonus = World->SpawnActor<ABonusBase>(BonusesConfig->BonusClasses[index],
		Position, FRotator::ZeroRotator);
	Bonus->Init(BonusFallSpeed,BallSpawner,BatBase);
	Bonuses.Add(Bonus);
}

void BonusFactory::SpawnBonusWithProbability(FVector Position, float Probability)
{
	if(FMath::RandRange(0.f,1.f)<=Probability)
	{
		SpawnBonus(Position);
	}
}

void BonusFactory::RevertBonuses()
{
	for (int i = Bonuses.Num() - 1;i >= 0;i--)
	{
		Bonuses[i]->InactivateBonus();
		Bonuses[i]->Destroy();
		Bonuses.RemoveAt(i);
	}
}

