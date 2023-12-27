// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\..\Intermediate\ProjectFiles\Delegates.h"
#include "BlockBase.h"
#include "EmptyActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerBricks.generated.h"

UCLASS(Abstract, Blueprintable)
class GAMEPLAYLEVEL_API ASpawnerBricks : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerBricks();

	UPROPERTY(EditAnyWhere, BlueprintReadonly)
		AEmptyActor* FirstPivot;

	UPROPERTY(EditAnyWhere, BlueprintReadonly)
		AEmptyActor* SecondPivot;

	UPROPERTY(EditAnyWhere);
		TSubclassOf<ABlockBase> BlockClass;

	UPROPERTY(EditAnyWhere)
		float Padding;

	NoParamDelegate OnAllBlocksDestroyed;

	BlockBaseDelegate OnDestroyBlock;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		bool IsValidBlockPosition(int Column, int Row);

	UFUNCTION(BlueprintImplementableEvent)
		void RandomizeBlockPattern();
	
	UPROPERTY(BlueprintReadOnly)
		int Rows;
	UPROPERTY(BlueprintReadOnly)
	 int Columns;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void Init();

	UFUNCTION(BlueprintCallable)
		void SpawnBlocks();

	UFUNCTION(BlueprintCallable)
		void DestroyAllBlocks();
private:
	float X0, Y0, Z0;

	TArray<ABlockBase*> Blocks;
	UWorld* World;

	void RemoveBlock(ABlockBase* Block);
};
