#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "BallAccelerationBonus.generated.h"

UCLASS()
class GAMEPLAYLEVEL_API ABallAccelerationBonus : public ABonusBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float SpeedRatio;

private:
	virtual void EnableBonus() override;

	virtual void DisableBonus() override;
	
};
