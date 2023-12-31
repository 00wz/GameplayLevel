#include "BatScalerBonus.h"

void ABatScalerBonus::EnableBonus()
{
	auto CurrentScale=Bat->GetActorScale();
	Bat->SetActorScale3D(FVector{CurrentScale.X,CurrentScale.Y*WidthRatio,CurrentScale.Z});
}

void ABatScalerBonus::DisableBonus()
{
	auto CurrentScale=Bat->GetActorScale();
	Bat->SetActorScale3D(FVector{CurrentScale.X,CurrentScale.Y/WidthRatio,CurrentScale.Z});
}
