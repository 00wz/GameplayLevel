// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "BallBonus.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYLEVEL_API ABallBonus : public ABonusBase
{
	GENERATED_BODY()

	virtual void EnableBonus() override;

	virtual void DisableBonus() override;
	
};
