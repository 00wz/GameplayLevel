#include "SpawnerBricks.h"
#include "EmptyActor.h"
#include "BlockBase.h"

ASpawnerBricks::ASpawnerBricks()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnerBricks::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	Init();
}

void ASpawnerBricks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerBricks::Init()
{
	auto PivotLocation1 = FirstPivot->GetTransform().GetLocation();
	auto PivotLocation2 = SecondPivot->GetTransform().GetLocation();
	float Top, Bottom, Left, Right;

	if (PivotLocation1.X > PivotLocation2.X)
	{
		Top = PivotLocation1.X;
		Bottom = PivotLocation2.X;
	}
	else
	{
		Top = PivotLocation2.X;
		Bottom = PivotLocation1.X;
	}

	if (PivotLocation1.Y > PivotLocation2.Y)
	{
		Right = PivotLocation1.Y;
		Left = PivotLocation2.Y;
	}
	else
	{
		Right = PivotLocation2.Y;
		Left = PivotLocation1.Y;
	}

	float Width = Right - Left;
	Columns = (int)(Width / Padding);
	Y0 = (Width - (Padding* Columns))/2+Left;

	float Height = Top - Bottom;
	Rows = (int)(Height / Padding);
	X0 = (Height - (Padding * Rows)) / 2 + Bottom;

	Z0 = (PivotLocation1.Z + PivotLocation2.Z) / 2;
}

void ASpawnerBricks::SpawnBlocks()
{
	RandomizeBlockPattern();
	float posX = X0;
	for(int r = 0;r <= Rows;r++)
	{
		float posY = Y0;
		for (int c = 0;c <= Columns;c++)
		{
			if (IsValidBlockPosition(c, r))
			{
				auto Block = World->SpawnActor<ABlockBase>(BlockClass, FVector{ posX,posY, Z0 }, FRotator::ZeroRotator);
				Blocks.Add(Block);
				Block->OnDestroyBlock.BindUObject(this, &ASpawnerBricks::RemoveBlock);
			}
			posY += Padding;
		}
		posX += Padding;
	}
}

void ASpawnerBricks::DestroyAllBlocks()
{
	for (int i = Blocks.Num()-1;i >=0;i--)
	{
		Blocks[i]->Destroy();
	}
}

void ASpawnerBricks::RemoveBlock(ABlockBase* Block)
{
	Blocks.Remove(Block);
	OnDestroyBlock.ExecuteIfBound(Block);
	if (Blocks.Num() <= 0)
	{
		OnAllBlocksDestroyed.ExecuteIfBound();
	}
}

