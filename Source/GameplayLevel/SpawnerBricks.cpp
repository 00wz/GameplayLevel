// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerBricks.h"
#include "EmptyActor.h"
#include "BlockBase.h"
// Sets default values
ASpawnerBricks::ASpawnerBricks()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//TSubclassOf<AActor> ActorClass{};
	/*
	auto Pivot1 = GetWorld()->SpawnActor<AActor>();
	auto Pivot2 = GetWorld()->SpawnActor<AActor>();
	Pivot1->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	Pivot2->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	*/
	
	
	//auto Pivot2 = GetWorld()->SpawnActor(AEmptyActor::StaticClass());
	//Pivot1->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	//Pivot2->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	
}

// Called when the game starts or when spawned
void ASpawnerBricks::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	Init();
	//SpawnBlocks();
}

// Called every frame
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
	//GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Right=%f	Left=%f"), Right, Left));
	//GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Top=%f	Bottom=%f"), Top, Bottom));
	//GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("X0=%f	Y0=%f"), X0, Y0));
	//GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Columns=%d	Rows=%d"), Columns, Rows));
}

void ASpawnerBricks::SpawnBlocks()
{
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
	if (Blocks.Num() <= 0)
	{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Win!!!")));
		OnAllBlocksDestroyed.ExecuteIfBound();
	}
}

